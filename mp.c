#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "gpg.h"
#include "packet.h"
#include "iobuf.h"
#include "options.h"
#include "util.h"
#include "cipher.h"
#include "keydb.h"
#include "filter.h"
#include "main.h"
#include "status.h"
#include "i18n.h"

extern int status;

struct kidlist_item {
    struct kidlist_item *next;
    u32 kid[2];
    int pubkey_algo;
    int reason;
};

/****************
 * Structure to hold the context
 */
typedef struct mainproc_context *CTX;
struct mainproc_context
{
  struct mainproc_context *anchor;  /* May be useful in the future. */
  PKT_public_key *last_pubkey;
  PKT_secret_key *last_seckey;
  PKT_user_id     *last_user_id;
  md_filter_context_t mfx;
  int sigs_only;    /* Process only signatures and reject all other stuff. */
  int encrypt_only; /* Process only encryption messages. */

  /* Name of the file with the complete signature or the file with the
     detached signature.  This is currently only used to deduce the
     file name of the data file if that has not been given. */
  const char *sigfilename;

  /* A structure to describe the signed data in case of a detached
     signature. */
  struct
  {
    /* A file descriptor of the the signed data.  Only used if not -1. */
    int data_fd;
    /* A list of filenames with the data files or NULL. This is only
       used if DATA_FD is -1. */
    strlist_t data_names;
    /* Flag to indicated that either one of the next previous fieldss
       is used.  This is only needed for better readability. */
    int used;
  } signed_data;

  DEK *dek;
  int last_was_session_key;
  KBNODE list;      /* The current list of packets. */
  int have_data;
  IOBUF iobuf;      /* Used to get the filename etc. */
  int trustletter;  /* Temporary usage in list_node. */
  ulong symkeys;
  struct kidlist_item *pkenc_list; /* List of encryption packets. */
  int any_sig_seen;  /* Set to true if a signature packet has been seen. */
};

int do_proc_packets( CTX c, IOBUF a );

static void
proc_encrypted( CTX c, PACKET *pkt )
{
    int result = 0;

    if (!opt.quiet)
      {
	/*if(c->symkeys>1)
	  log_info(_("encrypted with %lu passphrases\n"),c->symkeys);
	else if(c->symkeys==1)
	  log_info(_("encrypted with 1 passphrase\n"));
        print_pkenc_list ( c->pkenc_list, 1 );
        print_pkenc_list ( c->pkenc_list, 0 ); */
      }

    /* FIXME: Figure out the session key by looking at all pkenc packets. */


    write_status( STATUS_BEGIN_DECRYPTION );

    /*log_debug("dat: %sencrypted data\n", c->dek?"":"conventional ");*/
    if( opt.list_only )
	result = -1;
    else if( !c->dek && !c->last_was_session_key ) {
        int algo;
        STRING2KEY s2kbuf, *s2k = NULL;

	if(opt.override_session_key)
	  {
	    c->dek = xmalloc_clear( sizeof *c->dek );
	    // result=get_override_session_key(c->dek, opt.override_session_key); // FIXME
	    if(result)
	      {
		xfree(c->dek);
		c->dek = NULL;
	      }
	  }
	else
	  {
	    /* Assume this is old style conventional encrypted data. */
	    algo = opt.def_cipher_algo;
	    if ( algo )
	      log_info (_("assuming %s encrypted data\n"),
                        openpgp_cipher_algo_name (algo));
	    else if ( openpgp_cipher_test_algo (CIPHER_ALGO_IDEA) )
	      {
		algo = opt.def_cipher_algo;
		if (!algo)
		  algo = opt.s2k_cipher_algo;
		idea_cipher_warn(1);
		log_info (_("IDEA cipher unavailable, "
			    "optimistically attempting to use %s instead\n"),
			  openpgp_cipher_algo_name (algo));
	      }
	    else
	      {
		algo = CIPHER_ALGO_IDEA;
		if (!opt.s2k_digest_algo)
		  {
		    /* If no digest is given we assume MD5 */
		    s2kbuf.mode = 0;
		    s2kbuf.hash_algo = DIGEST_ALGO_MD5;
		    s2k = &s2kbuf;
		  }
		log_info (_("assuming %s encrypted data\n"), "IDEA");
	      }

	    c->dek = passphrase_to_dek ( NULL, 0, algo, s2k, 3, NULL, NULL );
	    if (c->dek)
	      c->dek->algo_info_printed = 1;
	  }
    }
    else if( !c->dek )
	result = G10ERR_NO_SECKEY;
    if( !result )
	result = decrypt_data( c, pkt->pkt.encrypted, c->dek );

    if( result == -1 )
	;
    else if( !result || (gpg_err_code (result) == GPG_ERR_BAD_SIGNATURE
                         && opt.ignore_mdc_error)) {
	write_status( STATUS_DECRYPTION_OKAY );
	if( opt.verbose > 1 )
	    log_info(_("decryption okay\n"));
	if( pkt->pkt.encrypted->mdc_method && !result )
	    write_status( STATUS_GOODMDC );
	// else if(!opt.no_mdc_warn); // FIXME
	    // log_info (_("WARNING: message was not integrity protected\n"));
	if(opt.show_session_key)
	  {
	    int i;
	    char *buf = xmalloc ( c->dek->keylen*2 + 20 );
	    sprintf ( buf, "%d:", c->dek->algo );
	    for(i=0; i < c->dek->keylen; i++ )
	      sprintf(buf+strlen(buf), "%02X", c->dek->key[i] );
	    log_info( "session key: `%s'\n", buf );
	    write_status_text ( STATUS_SESSION_KEY, buf );
	  }
    }
    else if( result == G10ERR_BAD_SIGN ) {
	log_error(_("WARNING: encrypted message has been manipulated!\n"));
	write_status( STATUS_BADMDC );
	write_status( STATUS_DECRYPTION_FAILED );
    }
    else {
        if (gpg_err_code (result) == GPG_ERR_BAD_KEY
	    && *c->dek->s2k_cacheid != '\0')
	  {
	    log_debug(_("cleared passphrase cached with ID: %s\n"),
		      c->dek->s2k_cacheid);
	    // passphrase_clear_cache (NULL, c->dek->s2k_cacheid, 0); // FIXME
	  }
	write_status( STATUS_DECRYPTION_FAILED );
	// log_error(_("decryption failed: %s\n"), g10_errstr(result));
	status = 0;
	/* Hmmm: does this work when we have encrypted using multiple
	 * ways to specify the session key (symmmetric and PK)*/
    }
    //xfree(c->dek); c->dek = NULL;
    free_packet(pkt);
    c->last_was_session_key = 0;
    write_status( STATUS_END_DECRYPTION );
}


static void
proc_plaintext( CTX c, PACKET *pkt )
{
    PKT_plaintext *pt = pkt->pkt.plaintext;
    int any, clearsig, only_md5, rc;
    KBNODE n;

    int literals_seen = 0;
    literals_seen++;

    if( pt->namelen == 8 && !memcmp( pt->name, "_CONSOLE", 8 ) )
	log_info(_("NOTE: sender requested \"for-your-eyes-only\"\n"));
    else if( opt.verbose )
	log_info(_("original file name='%.*s'\n"), pt->namelen, pt->name);
    free_md_filter_context( &c->mfx );
    if (gcry_md_open (&c->mfx.md, 0, 0))
      BUG ();
    /* fixme: we may need to push the textfilter if we have sigclass 1
     * and no armoring - Not yet tested
     * Hmmm, why don't we need it at all if we have sigclass 1
     * Should we assume that plaintext in mode 't' has always sigclass 1??
     * See: Russ Allbery's mail 1999-02-09
     */
    any = clearsig = only_md5 = 0;
    for(n=c->list; n; n = n->next )
      {
	if( n->pkt->pkttype == PKT_ONEPASS_SIG )
	  {
  	    /* For the onepass signature case */
	    if( n->pkt->pkt.onepass_sig->digest_algo )
	      {
		gcry_md_enable (c->mfx.md,
                                n->pkt->pkt.onepass_sig->digest_algo);
		if( !any && n->pkt->pkt.onepass_sig->digest_algo
		    == DIGEST_ALGO_MD5 )
		  only_md5 = 1;
		else
		  only_md5 = 0;
		any = 1;
	      }
	    if( n->pkt->pkt.onepass_sig->sig_class != 0x01 )
	      only_md5 = 0;
	  }
	else if( n->pkt->pkttype == PKT_GPG_CONTROL
                 && n->pkt->pkt.gpg_control->control
		 == CTRLPKT_CLEARSIGN_START )
	  {
	    /* For the clearsigned message case */
            size_t datalen = n->pkt->pkt.gpg_control->datalen;
            const byte *data = n->pkt->pkt.gpg_control->data;

            /* check that we have at least the sigclass and one hash */
            if ( datalen < 2 )
	      log_fatal("invalid control packet CTRLPKT_CLEARSIGN_START\n");
            /* Note that we don't set the clearsig flag for not-dash-escaped
             * documents */
            clearsig = (*data == 0x01);
            for( data++, datalen--; datalen; datalen--, data++ )
	        gcry_md_enable (c->mfx.md, *data);
            any = 1;
            break;  /* Stop here as one-pass signature packets are not
                       expected.  */
	  }
	else if(n->pkt->pkttype==PKT_SIGNATURE)
	  {
	    /* For the SIG+LITERAL case that PGP used to use. */
	    gcry_md_enable ( c->mfx.md, n->pkt->pkt.signature->digest_algo );
	    any=1;
	  }
      }

    if( !any && !opt.skip_verify )
      {
	/* This is for the old GPG LITERAL+SIG case.  It's not legal
	   according to 2440, so hopefully it won't come up that
	   often.  There is no good way to specify what algorithms to
	   use in that case, so these three are the historical
	   answer. */
	gcry_md_enable( c->mfx.md, DIGEST_ALGO_RMD160 );
	gcry_md_enable( c->mfx.md, DIGEST_ALGO_SHA1 );
	gcry_md_enable( c->mfx.md, DIGEST_ALGO_MD5 );
      }
    if( opt.pgp2_workarounds && only_md5 && !opt.skip_verify ) {
	/* This is a kludge to work around a bug in pgp2.  It does only
	 * catch those mails which are armored.  To catch the non-armored
	 * pgp mails we could see whether there is the signature packet
	 * in front of the plaintext.  If someone needs this, send me a patch.
	 */
      if ( gcry_md_open (&c->mfx.md2, DIGEST_ALGO_MD5, 0) )
        BUG ();
    }
    if ( DBG_HASHING ) {
	gcry_md_debug ( c->mfx.md, "verify" );
	if ( c->mfx.md2  )
	    gcry_md_debug ( c->mfx.md2, "verify2" );
    }

    rc=0;

    if (literals_seen>1)
      {
	log_info (_("WARNING: multiple plaintexts seen\n"));

	if (!opt.flags.allow_multiple_messages)
	  {
            write_status_text (STATUS_ERROR, "proc_pkt.plaintext 89_BAD_DATA");
	    log_inc_errorcount ();
	    rc = gpg_error (GPG_ERR_UNEXPECTED);
	  }
      }

    if(!rc)
      {
        rc = handle_plaintext( pt, &c->mfx, c->sigs_only, clearsig );
        if ( gpg_err_code (rc) == GPG_ERR_EACCES && !c->sigs_only )
          {
            /* Can't write output but we hash it anyway to check the
               signature. */
            rc = handle_plaintext( pt, &c->mfx, 1, clearsig );
          }
      }

    if( rc )
	log_error( "handle plaintext failed: %s\n", g10_errstr(rc));
    free_packet(pkt);
    c->last_was_session_key = 0;

    /* We add a marker control packet instead of the plaintext packet.
     * This is so that we can later detect invalid packet sequences.
     */
    n = new_kbnode (create_gpg_control (CTRLPKT_PLAINTEXT_MARK, NULL, 0));
    if (c->list)
        add_kbnode (c->list, n);
    else
        c->list = n;
}


static int
proc_compressed_cb( IOBUF a, void *info )
{
  if ( ((CTX)info)->signed_data.used
       && ((CTX)info)->signed_data.data_fd != -1)
    return proc_signature_packets_by_fd (info, a,
                                         ((CTX)info)->signed_data.data_fd);
  else
    return proc_signature_packets (info, a,
                                   ((CTX)info)->signed_data.data_names,
                                   ((CTX)info)->sigfilename );
}

static int
proc_encrypt_cb( IOBUF a, void *info )
{
    return proc_encryption_packets( info, a );
}

static void
proc_compressed( CTX c, PACKET *pkt )
{
    PKT_compressed *zd = pkt->pkt.compressed;
    int rc;

    /*printf("zip: compressed data packet\n");*/
    if (c->sigs_only)
	rc = handle_compressed( c, zd, proc_compressed_cb, c );
    else if( c->encrypt_only )
	rc = handle_compressed( c, zd, proc_encrypt_cb, c );
    else
	rc = handle_compressed( c, zd, NULL, NULL );
    if( rc )
	log_error("uncompressing failed: %s\n", g10_errstr(rc));
    free_packet(pkt);
    c->last_was_session_key = 0;
}

static void
proc_symkey_enc( CTX c, PACKET *pkt )
{
    PKT_symkey_enc *enc;

    enc = pkt->pkt.symkey_enc;
    if (!enc)
        log_error ("invalid symkey encrypted packet\n");
    else if(!c->dek)
      {
        int algo = enc->cipher_algo;
	const char *s = openpgp_cipher_algo_name (algo);
	if (!openpgp_cipher_test_algo (algo))
	  {
	    if(!opt.quiet)
	      {
		if(enc->seskeylen)
		  log_info(_("%s encrypted session key\n"), s );
		/* else
		  log_info(_("%s encrypted data\n"), s ); */
	      }
	  }
	else
	  log_error(_("encrypted with unknown algorithm this %d\n"), algo );

	if(openpgp_md_test_algo (enc->s2k.hash_algo))
	  {
	    log_error(_("passphrase generated with unknown digest"
			" algorithm %d\n"),enc->s2k.hash_algo);
	    s=NULL;
	  }

	c->last_was_session_key = 2;
	if(!s || opt.list_only)
	  goto leave;

	if(opt.override_session_key)
	  {
	    c->dek = xmalloc_clear( sizeof *c->dek );
	    /*if(get_override_session_key(c->dek, opt.override_session_key))
	      {
		xfree(c->dek);
		c->dek = NULL;
	      } */ // FIXME
	  }
	else
	  {
	    c->dek = passphrase_to_dek (NULL, 0, algo, &enc->s2k, 3,
                                        NULL, NULL);
	    if(c->dek)
	      {
		c->dek->symmetric=1;

		/* FIXME: This doesn't work perfectly if a symmetric
		   key comes before a public key in the message - if
		   the user doesn't know the passphrase, then there is
		   a chance that the "decrypted" algorithm will happen
		   to be a valid one, which will make the returned dek
		   appear valid, so we won't try any public keys that
		   come later. */
		if(enc->seskeylen)
		  {
		    /*if(symkey_decrypt_seskey(c->dek, enc->seskey,
					     enc->seskeylen))
		      {
			xfree(c->dek);
			c->dek=NULL;
		      } */ // FIXME madar
		  }
		else
		  c->dek->algo_info_printed = 1;
	      }
	  }
      }

 leave:
    c->symkeys++;
    free_packet(pkt);
}

int
proc_packets( void *anchor, IOBUF a )
{
    int rc;
    CTX c = xmalloc_clear( sizeof *c );

    c->anchor = anchor;
    rc = do_proc_packets( c, a );
    xfree( c );
    return rc;
}


int
proc_signature_packets( void *anchor, IOBUF a,
			strlist_t signedfiles, const char *sigfilename )
{
    CTX c = xmalloc_clear( sizeof *c );
    int rc;

    c->anchor = anchor;
    c->sigs_only = 1;

    c->signed_data.data_fd = -1;
    c->signed_data.data_names = signedfiles;
    c->signed_data.used = !!signedfiles;

    c->sigfilename = sigfilename;
    rc = do_proc_packets( c, a );

    /* If we have not encountered any signature we print an error
       messages, send a NODATA status back and return an error code.
       Using log_error is required because verify_files does not check
       error codes for each file but we want to terminate the process
       with an error. */
    if (!rc && !c->any_sig_seen)
      {
	write_status_text (STATUS_NODATA, "4");
        log_error (_("no signature found\n"));
        rc = G10ERR_NO_DATA;
      }

    /* Propagate the signature seen flag upward. Do this only on
       success so that we won't issue the nodata status several
       times. */
    if (!rc && c->anchor && c->any_sig_seen)
      c->anchor->any_sig_seen = 1;

    xfree( c );
    return rc;
}


int
proc_signature_packets_by_fd (void *anchor, IOBUF a, int signed_data_fd )
{
  int rc;
  CTX c = xcalloc (1, sizeof *c);

  c->anchor = anchor;
  c->sigs_only = 1;

  c->signed_data.data_fd = signed_data_fd;
  c->signed_data.data_names = NULL;
  c->signed_data.used = (signed_data_fd != -1);

  rc = do_proc_packets ( c, a );

  /* If we have not encountered any signature we print an error
     messages, send a NODATA status back and return an error code.
     Using log_error is required because verify_files does not check
     error codes for each file but we want to terminate the process
     with an error. */
  if (!rc && !c->any_sig_seen)
    {
      write_status_text (STATUS_NODATA, "4");
      log_error (_("no signature found\n"));
      rc = gpg_error (GPG_ERR_NO_DATA);
    }

  /* Propagate the signature seen flag upward. Do this only on success
     so that we won't issue the nodata status several times. */
  if (!rc && c->anchor && c->any_sig_seen)
    c->anchor->any_sig_seen = 1;

  xfree ( c );
  return rc;
}


int
proc_encryption_packets( void *anchor, IOBUF a )
{
    CTX c = xmalloc_clear( sizeof *c );
    int rc;

    c->anchor = anchor;
    c->encrypt_only = 1;
    rc = do_proc_packets( c, a );
    xfree( c );
    return rc;
}

int
do_proc_packets( CTX c, IOBUF a )
{
    PACKET *pkt = xmalloc( sizeof *pkt );
    int rc=0;
    int any_data=0;
    int newpkt;

    c->iobuf = a;
    init_packet(pkt);
    while( (rc=parse_packet(a, pkt)) != -1 ) {
	any_data = 1;
	if( rc ) {
	    free_packet(pkt);
            /* stop processing when an invalid packet has been encountered
             * but don't do so when we are doing a --list-packets. */
	    if (gpg_err_code (rc) == GPG_ERR_INV_PACKET
                && opt.list_packets != 2 )
		break;
	    continue;
	}
	newpkt = -1;
	if( opt.list_packets ) {
	    switch( pkt->pkttype ) {
	      case PKT_PUBKEY_ENC:  break;//proc_pubkey_enc( c, pkt ); break; // FIXME
	      case PKT_SYMKEY_ENC:  proc_symkey_enc( c, pkt ); break;
	      case PKT_ENCRYPTED:
	      case PKT_ENCRYPTED_MDC: proc_encrypted( c, pkt ); break;
	      case PKT_COMPRESSED:  proc_compressed( c, pkt ); break;
	      default: newpkt = 0; break;
	    }
	}
	else if( c->sigs_only ) {
	    switch( pkt->pkttype ) {
	      case PKT_PUBLIC_KEY:
	      case PKT_SECRET_KEY:
	      case PKT_USER_ID:
	      case PKT_SYMKEY_ENC:
	      case PKT_PUBKEY_ENC:
	      case PKT_ENCRYPTED:
	      case PKT_ENCRYPTED_MDC:
                write_status_text( STATUS_UNEXPECTED, "0" );
		rc = G10ERR_UNEXPECTED;
		goto leave;
	      case PKT_SIGNATURE:   break;//newpkt = add_signature( c, pkt ); break; //FIXME
	      case PKT_PLAINTEXT:   proc_plaintext( c, pkt ); break;
	      case PKT_COMPRESSED:  proc_compressed( c, pkt ); break;
	      case PKT_ONEPASS_SIG: break;//newpkt = add_onepass_sig( c, pkt ); break; // FIXME
              case PKT_GPG_CONTROL: break; // newpkt = add_gpg_control(c, pkt); break; // FIXME
	      default: newpkt = 0; break;
	    }
	}
	else if( c->encrypt_only ) {
	    switch( pkt->pkttype ) {
	      case PKT_PUBLIC_KEY:
	      case PKT_SECRET_KEY:
	      case PKT_USER_ID:
                write_status_text( STATUS_UNEXPECTED, "0" );
		rc = G10ERR_UNEXPECTED;
		goto leave;
	      case PKT_SIGNATURE:   break; //newpkt = add_signature( c, pkt ); break; //FIXME
	      case PKT_SYMKEY_ENC:  proc_symkey_enc( c, pkt ); break;
	      case PKT_PUBKEY_ENC:  break;//proc_pubkey_enc( c, pkt ); break; // FIXME
	      case PKT_ENCRYPTED:
	      case PKT_ENCRYPTED_MDC: proc_encrypted( c, pkt ); break;
	      case PKT_PLAINTEXT:   proc_plaintext( c, pkt ); break;
	      case PKT_COMPRESSED:  proc_compressed( c, pkt ); break;
	      case PKT_ONEPASS_SIG: break; //newpkt = add_onepass_sig( c, pkt ); break;
	      case PKT_GPG_CONTROL: break; //newpkt = add_gpg_control(c, pkt); break;
	      default: newpkt = 0; break;
	    }
	}
	else {
	    switch( pkt->pkttype ) {
	      case PKT_PUBLIC_KEY:
	      case PKT_SECRET_KEY:
		//release_list( c ); // FIXME
		c->list = new_kbnode( pkt );
		newpkt = 1;
		break;
	      case PKT_PUBLIC_SUBKEY:
	      case PKT_SECRET_SUBKEY:
		//newpkt = add_subkey( c, pkt ); //FIXME
		break;
	      case PKT_USER_ID:     break; //newpkt = add_user_id( c, pkt ); break;
	      case PKT_SIGNATURE:   break; //newpkt = add_signature( c, pkt ); break;
	      case PKT_PUBKEY_ENC:  break;//proc_pubkey_enc( c, pkt ); break;
	      case PKT_SYMKEY_ENC:  proc_symkey_enc( c, pkt ); break;
	      case PKT_ENCRYPTED:
	      case PKT_ENCRYPTED_MDC: proc_encrypted( c, pkt ); break;
	      case PKT_PLAINTEXT:   proc_plaintext( c, pkt ); break;
	      case PKT_COMPRESSED:  proc_compressed( c, pkt ); break;
	      case PKT_ONEPASS_SIG: break;//newpkt = add_onepass_sig( c, pkt ); break; // FIXME
              case PKT_GPG_CONTROL: break; // newpkt = add_gpg_control(c, pkt); break; // FIXME
	      case PKT_RING_TRUST:  break; //newpkt = add_ring_trust( c, pkt ); break; // FIXME
	      default: newpkt = 0; break;
	    }
	}
        /* This is a very ugly construct and frankly, I don't remember why
         * I used it.  Adding the MDC check here is a hack.
         * The right solution is to initiate another context for encrypted
         * packet and not to reuse the current one ...  It works right
         * when there is a compression packet inbetween which adds just
         * an extra layer.
         * Hmmm: Rewrite this whole module here??
         */
	if( pkt->pkttype != PKT_SIGNATURE && pkt->pkttype != PKT_MDC )
	    c->have_data = pkt->pkttype == PKT_PLAINTEXT;

	if( newpkt == -1 )
	    ;
	else if( newpkt ) {
	    pkt = xmalloc( sizeof *pkt );
	    init_packet(pkt);
	}
	else
	    free_packet(pkt);
    }
    if( rc == G10ERR_INVALID_PACKET )
	write_status_text( STATUS_NODATA, "3" );
    if( any_data )
	rc = 0;
    else if( rc == -1 )
	write_status_text( STATUS_NODATA, "2" );


  leave:
    //release_list( c );
    //xfree(c->dek);
    free_packet( pkt );
    xfree( pkt );
    free_md_filter_context( &c->mfx );
    return rc;
}


