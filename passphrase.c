/* passphrase.c -  Get a passphrase
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004,
 *               2005, 2006, 2007, 2009 Free Software Foundation, Inc.
 *
 * This file is part of GnuPG.
 *
 * GnuPG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * GnuPG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif
#ifdef HAVE_LANGINFO_CODESET
#include <langinfo.h>
#endif

#include "gpg.h"
#include "util.h"
#include "options.h"
#include "ttyio.h"
#include "cipher.h"
#include "keydb.h"
#include "main.h"
#include "i18n.h"
#include "status.h"
#include "cipher.h"

static char *fd_passwd = NULL;
static char *next_pw = NULL;
static char *last_pw = NULL;


/* Hash a passphrase using the supplied s2k.
   Always needs: dek->algo, s2k->mode, s2k->hash_algo.  */
static void
hash_passphrase ( DEK *dek, char *pw, STRING2KEY *s2k)
{
  gcry_md_hd_t md;
  int pass, i;
  int used = 0;
  int pwlen = strlen(pw);

  assert ( s2k->hash_algo );
  dek->keylen = openpgp_cipher_get_algo_keylen (dek->algo);
  if ( !(dek->keylen > 0 && dek->keylen <= DIM(dek->key)) )
    BUG();

  if (gcry_md_open (&md, s2k->hash_algo, 1))
    BUG ();
  for (pass=0; used < dek->keylen ; pass++ )
    {
      if ( pass )
        {
          gcry_md_reset (md);
          for (i=0; i < pass; i++ ) /* Preset the hash context.  */
            gcry_md_putc (md, 0 );
	}

      if ( s2k->mode == 1 || s2k->mode == 3 )
        {
          int len2 = pwlen + 8;
          ulong count = len2;

          if ( s2k->mode == 3 )
            {
              count = S2K_DECODE_COUNT(s2k->count);
              if ( count < len2 )
                count = len2;
	    }

          /* Fixme: To avoid DoS attacks by sending an sym-encrypted
             packet with a very high S2K count, we should either cap
             the iteration count or CPU seconds based timeout.  */

          /* A little bit complicated because we need a ulong for count. */
          while ( count > len2 )  /* maybe iterated+salted */
            {
              gcry_md_write ( md, s2k->salt, 8 );
              gcry_md_write ( md, pw, pwlen );
              count -= len2;
	    }
          if ( count < 8 )
            gcry_md_write ( md, s2k->salt, count );
          else
            {
              gcry_md_write ( md, s2k->salt, 8 );
              count -= 8;
              gcry_md_write ( md, pw, count );
	    }
	}
      else
        gcry_md_write ( md, pw, pwlen );
      gcry_md_final( md );

      i = gcry_md_get_algo_dlen ( s2k->hash_algo );
      if ( i > dek->keylen - used )
        i = dek->keylen - used;

      memcpy (dek->key+used, gcry_md_read (md, s2k->hash_algo), i);
      used += i;
    }
  gcry_md_close(md);
}



int
have_static_passphrase()
{
  return !!fd_passwd && opt.batch;
}

/****************
 * Set the passphrase to be used for the next query and only for the next
 * one.
 */
void
set_next_passphrase( const char *s )
{
  xfree(next_pw);
  next_pw = NULL;
  if ( s )
    {
      next_pw = xmalloc_secure( strlen(s)+1 );
      strcpy (next_pw, s );
    }
}

/****************
 * Get the last passphrase used in passphrase_to_dek.
 * Note: This removes the passphrase from this modules and
 * the caller must free the result.  May return NULL:
 */
char *
get_last_passphrase()
{
  char *p = last_pw;
  last_pw = NULL;
  return p;
}

/* As if we had used the passphrase - make it the last_pw. */
void
next_to_last_passphrase(void)
{
  if (next_pw)
    {
      last_pw=next_pw;
      next_pw=NULL;
    }
}

/* Here's an interesting question: since this passphrase was passed in
   on the command line, is there really any point in using secure
   memory for it?  I'm going with 'yes', since it doesn't hurt, and
   might help in some small way (swapping). */

void
set_passphrase_from_string(const char *pass)
{
  xfree (fd_passwd);
  fd_passwd = xmalloc_secure(strlen(pass)+1);
  strcpy (fd_passwd, pass);
}


void
read_passphrase_from_fd( int fd )
{
  int i, len;
  char *pw;

  if ( !opt.batch )
    { /* Not used but we have to do a dummy read, so that it won't end
         up at the begin of the message if the quite usual trick to
         prepend the passphtrase to the message is used. */
      char buf[1];

      while (!(read (fd, buf, 1) != 1 || *buf == '\n' ))
        ;
      *buf = 0;
      return;
    }

  for (pw = NULL, i = len = 100; ; i++ )
    {
      if (i >= len-1 )
        {
          char *pw2 = pw;
          len += 100;
          pw = xmalloc_secure( len );
          if( pw2 )
            {
              memcpy(pw, pw2, i );
              xfree (pw2);
            }
          else
            i=0;
	}
      if (read( fd, pw+i, 1) != 1 || pw[i] == '\n' )
        break;
    }
  pw[i] = 0;
  if (!opt.batch)
    tty_printf("\b\b\b   \n" );

  xfree ( fd_passwd );
  fd_passwd = pw;
}

/* Return a new DEK object Using the string-to-key sepcifier S2K.  Use
   KEYID and PUBKEY_ALGO to prompt the user.  Returns NULL is the user
   selected to cancel the passphrase entry and if CANCELED is not
   NULL, sets it to true.

   MODE 0:  Allow cached passphrase
        1:  Ignore cached passphrase
        2:  Ditto, but create a new key
        3:  Allow cached passphrase; use the S2K salt as the cache ID
        4:  Ditto, but create a new key
*/

extern char passphrase[128];

DEK dek;
DEK *
passphrase_to_dek_ext (u32 *keyid, int pubkey_algo,
                       int cipher_algo, STRING2KEY *s2k, int mode,
                       const char *tryagain_text,
                       const char *custdesc, const char *custprompt,
                       int *canceled)
{
  char *pw = NULL;
  STRING2KEY help_s2k;
  int dummy_canceled;
  char s2k_cacheidbuf[1+16+1]; // *s2k_cacheid = NULL;

  if (!canceled)
    canceled = &dummy_canceled;
  *canceled = 0;

  if ( !s2k )
    {
      assert (mode != 3 && mode != 4);
      /* This is used for the old rfc1991 mode
       * Note: This must match the code in encode.c with opt.rfc1991 set */
      s2k = &help_s2k;
      s2k->mode = 0;
      s2k->hash_algo = S2K_DIGEST_ALGO;
    }

  /* If we do not have a passphrase available in NEXT_PW and status
     information are request, we print them now. */
  if ( !next_pw && is_status_enabled() )
    {
      char buf[50];

      if ( keyid )
        {
          u32 used_kid[2];
          //char *us;

          if ( keyid[2] && keyid[3] )
            {
              used_kid[0] = keyid[2];
              used_kid[1] = keyid[3];
            }
          else
            {
              used_kid[0] = keyid[0];
              used_kid[1] = keyid[1];
            }

          //us = get_long_user_id_string ( keyid );
          //write_status_text ( STATUS_USERID_HINT, us );
          //xfree(us);

          snprintf (buf, sizeof buf -1, "%08lX%08lX %08lX%08lX %d 0",
                    (ulong)keyid[0], (ulong)keyid[1],
                    (ulong)used_kid[0], (ulong)used_kid[1],
                    pubkey_algo );

          //write_status_text ( STATUS_NEED_PASSPHRASE, buf );
	}
      else
        {
          snprintf (buf, sizeof buf -1, "%d %d %d",
                    cipher_algo, s2k->mode, s2k->hash_algo );
          //write_status_text ( STATUS_NEED_PASSPHRASE_SYM, buf );
	}
    }

  /* If we do have a keyID, we do not have a passphrase available in
     NEXT_PW, we are not running in batch mode and we do not want to
     ignore the passphrase cache (mode!=1), print a prompt with
     information on that key. */
  if ( keyid && !opt.batch && !next_pw && mode!=1 )
    {
      PKT_public_key *pk = xmalloc_clear( sizeof *pk );
       /*
      char *p;

      p = get_user_id_native(keyid);
      tty_printf ("\n");
      tty_printf (_("You need a passphrase to unlock the secret key for\n"
                    "user: \"%s\"\n"),p);
      xfree(p); */

/*      if ( !get_pubkey( pk, keyid ) )
        {
          const char *s = gcry_pk_algo_name ( pk->pubkey_algo );

          tty_printf (_("%u-bit %s key, ID %s, created %s"),
                      nbits_from_pk( pk ), s?s:"?", keystr(keyid),
                      strtimestamp(pk->timestamp) );
          if ( keyid[2] && keyid[3]
               && keyid[0] != keyid[2] && keyid[1] != keyid[3] )
            {
              if ( keystrlen () > 10 )
                {
                  tty_printf ("\n");
                  tty_printf (_("         (subkey on main key ID %s)"),
                              keystr(&keyid[2]) );
                }
              else
                tty_printf ( _(" (main key ID %s)"), keystr(&keyid[2]) );
            }
          tty_printf("\n");
	} */

      tty_printf("\n");
      if (pk)
        free_public_key( pk );
    }

  if ( next_pw )
    {
      /* Simply return the passphrase we already have in NEXT_PW. */
      pw = next_pw;
      next_pw = NULL;
    }
  else if ( have_static_passphrase () )
    {
      /* Return the passphrase we have stored in FD_PASSWD. */
      pw = xmalloc_secure ( strlen(fd_passwd)+1 );
      strcpy ( pw, fd_passwd );
    }
  else
    {
      if ((mode == 3 || mode == 4) && (s2k->mode == 1 || s2k->mode == 3))
	{
	  memset (s2k_cacheidbuf, 0, sizeof s2k_cacheidbuf);
	  *s2k_cacheidbuf = 'S';
	  bin2hex (s2k->salt, 8, s2k_cacheidbuf + 1);
	  // s2k_cacheid = s2k_cacheidbuf;
	}

      /* Divert to the gpg-agent. */
      pw = passphrase;
    }

  /* Hash the passphrase and store it in a newly allocated DEK object.
     Keep a copy of the passphrase in LAST_PW for use by
     get_last_passphrase(). */
  //dek = xmalloc_secure_clear ( sizeof *dek );
  memset(&dek, 0, sizeof(DEK));
  dek.algo = cipher_algo;
  if ( (!pw || !*pw) && (mode == 2 || mode == 4))
    dek.keylen = 0;
  else
    hash_passphrase (&dek, pw, s2k);
  return &dek;
}


DEK *
passphrase_to_dek (u32 *keyid, int pubkey_algo,
		   int cipher_algo, STRING2KEY *s2k, int mode,
                   const char *tryagain_text, int *canceled)
{
  return passphrase_to_dek_ext (keyid, pubkey_algo, cipher_algo,
                                s2k, mode, tryagain_text, NULL, NULL,
                                canceled);
}
