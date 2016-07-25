#include <Zaap.h>
#include <iostream>


using namespace zaap;
using namespace math;
using namespace graphics;
using namespace std;

graphics::Scene* scene;
Entity* m = nullptr;

void loadEntitys()
{
	//Flor
	Mesh mesh = API::Context::GetLoader()->loadOBJFile("res/flor.obj");
	TextureManager::LoadTexture2D("flor", "res/flor.jpg");
	TMeshManager::AddTMesh(TexturedMesh("flor", mesh, (graphics::Texture2D*)graphics::TextureManager::GetTexture("flor")));

	math::Vec3 v = math::Vec3(0, -1, 0);

	scene->addEntity(new Entity(TMeshManager::GetTMesh("flor"), v));

	//rock
	TextureManager::LoadTexture2D("rock", "res/rock.png");
	mesh = API::Context::GetLoader()->loadOBJFile("res/rock.obj");
	TMeshManager::AddTMesh(TexturedMesh("rock", mesh, (graphics::Texture2D*)graphics::TextureManager::GetTexture("rock")));
	
	v = math::Vec3(0, 1, 0);

	scene->addEntity(new Entity(TMeshManager::GetTMesh("rock"), v));
	//Cube
	mesh = API::Context::GetLoader()->loadOBJFile("res/cube.obj");
	TextureManager::LoadTexture2D("cube", "res/cube.png");

	TexturedMesh tMesh = graphics::TexturedMesh("cube", mesh, (graphics::Texture2D*)graphics::TextureManager::GetTexture("cube"));
	v = math::Vec3(0, 1, 5);
	scene->addEntity(new Entity(tMesh, v));

	v = math::Vec3(0, 1, -5);
	m = new Entity(tMesh, v);
	m->setScale(1.0f);
	scene->addEntity(m);

}


class Test : public Application
{
public:
	Test() : Application("Test", 800, 600, scene)
	{}

	void update() override {
		Application::update();

		m->increaseRotation(Vec3(1.0f, 1.0f, 1.0f));
		//m->addToScale(0.001f);
	}
};

int main()
{
	scene = new graphics::Scene();
	Test t;

	loadEntitys();

	t.start();

	t.cleanup();

	delete scene;

	return 0;
}
