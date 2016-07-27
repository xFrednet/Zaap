#include <Zaap.h>

using namespace zaap;
using namespace math;
using namespace graphics;
using namespace std;

Scene* scene = nullptr;
LightSetup *lightSetup = nullptr;
Light* light = nullptr;
Camera* camera = nullptr;
Entity* m1 = nullptr;
Entity* m2 = nullptr;

void loadEntitys()
{
	camera = new ControllableCamera();
	Renderer::SetCamera(camera);
	{
		lightSetup = new LightSetup();

		light = new Light(Vec3(0.0f, 10.0f, 0.0f));
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
		Entity* e = new Entity(TMeshManager::GetTMesh("flor"), v);
		e->setScale(5.0f);
		scene->addEntity(e);
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
		m2 = new Entity(tMesh, v);
		scene->addEntity(m2);
	}

	//Cube 2
	{
		v = Vec3(0, 1, -5);
		m1 = new Entity(tMesh, v);
		scene->addEntity(m1);
	}
}


class Test : public Application
{
public:
	Test() : Application("Test", 800, 600, scene)
	{}

	float count = 0.0f;
	
	void update() override {
		Application::update();

		float rot = 0.5f;
		m1->increaseRotation(Vec3(rot, rot, rot));
		m2->increaseRotation(Vec3(rot, rot, rot));
		count += 0.05f;
		//m2->setScale(sinf(count) / 5 + 1.5f);
		//m1->setScale(cosf(count) / 5 + 1.5f);
		m1->setScale(Vec3(cosf(count) + 1.1f, sinf(count) + 1.1f, sinf(count) + 1.1f));

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
