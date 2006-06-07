/* -----------------------------------------------------------------------------
 *
 * (c) The GHC Team, 1998-2004
 *
 * Message API for use inside the RTS.  All messages generated by the
 * RTS should go through one of the functions declared here, and we
 * also provide hooks so that messages from the RTS can be redirected
 * as appropriate.
 *
 * ---------------------------------------------------------------------------*/

#ifndef RTSMESSAGES_H
#define RTSMESSAGES_H

#include <stdarg.h>

/* -----------------------------------------------------------------------------
 * Message generation
 * -------------------------------------------------------------------------- */

/*
 * A fatal internal error: this is for errors that probably indicate
 * bugs in the RTS or compiler.  We normally output bug reporting
 * instructions along with the error message.
 *
 * barf() invokes (*fatalInternalErrorFn)().  This function is not
 * expected to return.
 */
extern void barf(const char *s, ...)
   GNUC3_ATTRIBUTE(__noreturn__);

extern void vbarf(const char *s, va_list ap)
   GNUC3_ATTRIBUTE(__noreturn__);

extern void _assertFail(const char *filename, unsigned int linenum)
   GNUC3_ATTRIBUTE(__noreturn__);

/*
 * An error condition which is caused by and/or can be corrected by
 * the user.
 *
 * errorBelch() invokes (*errorMsgFn)().
 */
extern void errorBelch(const char *s, ...)
   GNUC3_ATTRIBUTE(format (printf, 1, 2));

extern void verrorBelch(const char *s, va_list ap);

/*
 * A debugging message.  Debugging messages are generated either as a
 * virtue of having DEBUG turned on, or by being explicitly selected
 * via RTS options (eg. +RTS -Ds).
 *
 * debugBelch() invokes (*debugMsgFn)().
 */
extern void debugBelch(const char *s, ...)
   GNUC3_ATTRIBUTE(format (printf, 1, 2));

extern void vdebugBelch(const char *s, va_list ap);


/* Hooks for redirecting message generation: */

typedef void RtsMsgFunction(const char *, va_list);

extern RtsMsgFunction *fatalInternalErrorFn;
extern RtsMsgFunction *debugMsgFn;
extern RtsMsgFunction *errorMsgFn;

/* Default stdio implementation of the message hooks: */

extern RtsMsgFunction rtsFatalInternalErrorFn;
extern RtsMsgFunction rtsDebugMsgFn;
extern RtsMsgFunction rtsErrorMsgFn;

#endif /* RTSMESSAGES_H */
