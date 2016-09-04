#ifndef _RUBYCOREINTERFACE_H_
#define _RUBYCOREINTERFACE_H_
//=============================================================================
// TODO: Un1versal
//=============================================================================

#include "kvi_settings.h"
#include "KviKvsRunTimeContext.h"

#include <QString>
#include <QStringList>

#define KVI_RUBYCORECTRLCOMMAND_EXECUTE "execute"

typedef struct _KviRubyCoreCtrlCommand_execute
{
	unsigned int uSize;
	KviKvsRunTimeContext * pKvsContext;
	QString szContext;
	QString szCode;
	bool bExitOk;
	QString szRetVal;
	QString szError;
	QStringList lWarnings;
	QStringList lArgs;
	bool bQuiet;
} KviRubyCoreCtrlCommand_execute;

#define KVI_RUBYCORECTRLCOMMAND_DESTROY "destroy"

typedef struct _KviRubyCoreCtrlCommand_destroy
{
	unsigned int uSize;
	QString szContext;
} KviRubyCoreCtrlCommand_destroy;

#endif // !_RUBYCOREINTERFACE_H_
