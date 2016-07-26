#include <Zaap.h>

using namespace zaap;
using namespace math;
using namespace graphics;
using namespace std;

Scene* scene = nullptr;
LightSetup *lightSetup = nullptr;
Light* light = nullptr;
Camera* camera = nullptr;
Entity* m = nullptr;

void loadEntitys()
{
	camera = new ControllableCamera();
	Renderer::SetCamera(camera);
	{
		lightSetup = new LightSetup();

		light = new Light(Vec3(0.0f, 1.5f, 0.0f));
		lightSetup->add(light);

		scene->setLightSetup(lightSetup);
	}


	Mesh mesh;
	Vec3 v;
	
	//Flor
	{
		mesh = API::Context::GetLoader()->loadOBJFile("res/flor.obj");
		TextureManager::LoadTexture2D("flor", "res/flor.jpg");
		TMeshManager::AddTMesh(TexturedMesh("flor", mesh, (Texture2D*)TextureManager::GetTexture("flor")));

		v = Vec3(0, -1, 0);

		scene->addEntity(new Entity(TMeshManager::GetTMesh("flor"), v));
	}

	//rock
	{
		TextureManager::LoadTexture2D("rock", "res/rock.png");
		mesh = API::Context::GetLoader()->loadOBJFile("res/rock.obj");
		TMeshManager::AddTMesh(TexturedMesh("rock", mesh, (Texture2D*)TextureManager::GetTexture("rock")));
	
		v = Vec3(0, 1, 0);

		scene->addEntity(new Entity(TMeshManager::GetTMesh("rock"), v));
	}

	//Cube 1
	mesh = API::Context::GetLoader()->loadOBJFile("res/cube.obj");
	TextureManager::LoadTexture2D("cube", "res/cube.png");
	TexturedMesh tMesh("cube", mesh, (Texture2D*)TextureManager::GetTexture("cube"));
	{
		v = Vec3(0, 1, 5);
		scene->addEntity(new Entity(tMesh, v));
	}

	//Cube 2
	{
		v = Vec3(0, 1, -5);
		m = new Entity(tMesh, v);
		m->setScale(1.0f);
		scene->addEntity(m);
	}
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

		camera->update();
		light->setPosition(camera->getPosition());
	}
};

int main()
{
	scene = new Scene();
	
	Test t;
	loadEntitys();

	t.start();

	t.cleanup();

	return 0;
}
