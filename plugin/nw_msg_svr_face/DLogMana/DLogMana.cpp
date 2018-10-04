#include "DLogMana.h"

#define MAXLEN_LOG_DIR	256

using namespace google;

DLogMana::DLogMana(const char* dir, const char* module_name)
{
	if (!*dir || !*module_name)
		return ;

	google::InitGoogleLogging(module_name);
	
	char cmd[MAXLEN_LOG_DIR+32] = {0};	
	sprintf(cmd, "mkdir -p %s", dir);
	system(cmd);

	SetLogDestination(INFO, dir);
	SetLogDestination(WARNING, dir);
	SetLogDestination(ERROR, dir);
	SetLogDestination(FATAL, dir); 
}

DLogMana::~DLogMana()
{
	google::ShutdownGoogleLogging();
}
