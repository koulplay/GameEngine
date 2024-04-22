#include <GameEngineCore/application.h>

#include <iostream>
#include <memory>

class MyApp : public engine::Application{
	void OnUpdate() override{
		//std::cout << "Update frame: " << frame++ << std::endl;
	}
	int frame = 0;
};

int main(){
	std::cout << "GameEngineEditor" << std::endl;
	std::unique_ptr<MyApp> my_app = std::make_unique<MyApp>();

	int return_code = my_app->Start(1024, 768, "first app");

	std::cin.get();

	return return_code;
}