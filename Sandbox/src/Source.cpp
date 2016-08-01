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
Entity* lightCube = nullptr;

void loadEntitys()
{
	camera = new ControllableCamera(Vec3(12.0f, 12.0f, -1.0f), -90.0f, 30.0f);
	Renderer::SetCamera(camera);
	{
		lightSetup = new LightSetup();

		light = new Light(Vec3(0.0f, 10.0f, 0.0f), Vec3(1.0f, 0.0f, 1.0f));
		lightSetup->add(light);

		scene->setLightSetup(lightSetup);
	}

	Vec3 v;
	TexturedMesh *mesh = nullptr;
	
	//Test Model
	{
		API::Context::GetLoader()->loadMTLFile("res/Test.mtl");
		
		MeshManager::AddMesh(API::Context::GetLoader()->loadOBJFile("Test", "res/Test.obj", false));
		
		v = Vec3(0, 0, 0);
		scene->addEntity(new Entity(MeshManager::GetMesh("Test"), v));
	}
	
	//Flor
	{
		TextureManager::LoadTexture2D("flor", "res/flor.jpg");
		mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("flor", "res/flor.obj");
		mesh->setTexture((Texture2D*)TextureManager::GetTexture("flor"));
		//((TexturedMesh*)MeshManager::GetMesh("Test"))->setTexture((Texture2D*)TextureManager::GetTexture("flor"));
		MeshManager::AddMesh(mesh);

		v = Vec3(0, -1, 0);
		Entity* e = new Entity(MeshManager::GetMesh("flor"), v);
		e->setScale(5.0f);
		scene->addEntity(e);
	}

	//rock
	{
		TextureManager::LoadTexture2D("rock", "res/rock.png");
		mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("rock", "res/rock.obj");
		mesh->setTexture((Texture2D*)TextureManager::GetTexture("rock"));
		MeshManager::AddMesh(mesh);
	
		v = Vec3(0, 1, 0);

		scene->addEntity(new Entity(MeshManager::GetMesh("rock"), v));
	}

	//bench
	{
		TextureManager::LoadTexture2D("wood", "res/bench.jpg");
		mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("bench", "res/bench.obj");
		mesh->setTexture((Texture2D*)TextureManager::GetTexture("wood"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-5, 1, 0);

		scene->addEntity(new Entity(MeshManager::GetMesh("bench"), v));
	}

	//Cube 1
	TextureManager::LoadTexture2D("cube", "res/cube.png");
	mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("cube", "res/cube.obj");
	mesh->setTexture((Texture2D*)TextureManager::GetTexture("cube"));
	MeshManager::AddMesh(mesh);
	Mesh* tMesh = MeshManager::GetMesh("cube");
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

	//Light Cube
	{
		
		v = Vec3(0, -20, 0);
		lightCube = new Entity(tMesh, v);
		scene->addEntity(lightCube);
	}

	//Zaap frame
	{
		TextureManager::LoadTexture2D("zaap", "res/zaapLogo.png");
		mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("zaap", "res/zaapFrame.obj");
		mesh->setTexture((Texture2D*)TextureManager::GetTexture("zaap"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-7, 5, 0);
		scene->addEntity(new Entity(MeshManager::GetMesh("zaap"), v, Vec3(0.0f, 0.0f, 35.0f), Vec3(4.0f, 4.0f, 4.0f)));
	}
}

class Test : public Application
{
public:
	Test() : Application("Test", 852, 480, scene)
	{}

	float count = 0.0f;
	float count2 = 0.0f;

	void update() override {
		Application::update();

		float rot = 0.5f;
		m1->increaseRotation(Vec3(rot, rot, rot));
		m2->increaseRotation(Vec3(rot, rot, rot));
		count += 0.05f;
		m1->setScale(Vec3(cosf(count) + 1.1f, sinf(count) + 1.1f, sinf(count) + 1.1f));

		count2 += 0.0005f;
		light->setColor(Color(Vec3(1.0f, 1.0f, 1.0f) * (sinf(count2) * 0.25f + 0.75f)));
		
		light->setPosition(Vec3(0.0f, 100.0f, 100.0f * sinf(count2)));

		camera->update();
		lightCube->setPosition(light->getPosition());

		//light->setPosition(camera->getPosition());
	}
};

int main(void)
{
	scene = new Scene();
	
	Test t;
	loadEntitys();

	t.start();

	t.cleanup();

	return 0;
}
