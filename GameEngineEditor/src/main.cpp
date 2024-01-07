#include <GameEngineCore/Utils/test.h>

#include <iostream>



int main(){
	std::cout << "GameEngineEditor" << std::endl;

	engine::TellSomeThing();
	
	engine::ShowWindow();

	std::cin.get();
}