#include<iostream>
#include"WindowManager.h"
using namespace HandRecognition;
using namespace std;
int main(){
	cout << "Hello, World!!!" << endl;
	WindowManager::addWindow(WindowPtr(new Window("koko")), true);
	WindowManager::addWindow(WindowPtr(new Window("moka",100,100)));
	WindowManager::removeWindow("moka");
	WindowManager::cleanUp();
	return 0;
}