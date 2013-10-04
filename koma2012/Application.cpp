
/*Application*/
#include "Application.h"
#include "ApplicationProperty.h"
#include "Logger.h"

/*Audio&GraphicAdapter*/
#include "AudioAdapter.h"
#include "GraphicAdapter.h"
#include "InputAdapter.h"
#include "PackageManager.h"

#define DEF_CONSOLE_LOG	1
#define DEF_TEXT_LOG	1

Application::Application(){
	audioAdapter=NULL;
	graphicAdapter=NULL;
	inputAdapter=NULL;
	packageManager=NULL;
}

Application::~Application(){
}

bool Application::Init(int* argc,char** argv,HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	/* ���O�o�͗p�̃R���\�[����ʂ̍쐬 */
	AllocConsole();
	FILE* dfp;
	freopen_s(&dfp,"CONOUT$", "w", stdout);
	freopen_s(&dfp,"CONIN$", "r", stdin);

	/* �R���t�B�O�Ǘ��̏����� */
	ApplicationProperty::Init(argc,argv,hInstance,hPrevInstance,lpCmdLine,nCmdShow);
	string mySection = "Application";
	int ir=0;

	/* ���O�̏����� */
	ir=ApplicationProperty::ReadSetupInt(mySection,"ConsoleLog",DEF_CONSOLE_LOG);
	Logger::SetConsoleLog(ir!=0);
	ir=ApplicationProperty::ReadSetupInt(mySection,"TextLog",DEF_TEXT_LOG);
	Logger::SetTextLog(ir!=0);

	Logger::Println("[Application]	Start");
	Logger::Println("[Application]	Initialize");

	/* �O���t�B�b�N�̏����� */
	graphicAdapter = GraphicAdapter::CreateInstance();
	if(!graphicAdapter->Init()){
		Logger::Println("[Application]	Error : Graphic Initialize Fail");
		return false;
	}
	/* �I�[�f�B�I�̏����� */
	audioAdapter = AudioAdapter::CreateInstance();
	if(!audioAdapter->Init()){
		Logger::Println("[Application]	Error : Audio Initialize Fail");
		return false;
	}

	/* ���̓A�_�v�^�Q�̏����� */
	inputAdapter = InputAdapter::CreateInstance();
	if(!inputAdapter->Init()){
		Logger::Println("[Application]	Error : Input Initialize Fail");
		return false;
	}

	/* �p�b�P�[�W�Q�̏����� */
	packageManager = PackageManager::CreateInstance();
	if(!packageManager->Init(graphicAdapter->GetAPI(),audioAdapter->GetAPI(),inputAdapter->GetAPI())){
		Logger::Println("[Application]	Error : Package Initialize Fail");
		return false;
	}
	return true;
}

void Application::Close(){
	Logger::Println("[Application]	Close");

	//�p�b�P�[�W�̏I��
	if(packageManager!=NULL)packageManager->Close();
	if(audioAdapter!=NULL)audioAdapter->Close();
	if(graphicAdapter!=NULL)graphicAdapter->Close();
	if(inputAdapter!=NULL)inputAdapter->Close();

	PackageManager::DestroyInstance();
	AudioAdapter::DestroyInstance();
	GraphicAdapter::DestroyInstance();
	InputAdapter::DestroyInstance();

	Logger::Println("[Application]	End");
}

void Application::Run(){
	Logger::Println("[Application]	Run");

	audioAdapter->Run();
	graphicAdapter->Run();
}