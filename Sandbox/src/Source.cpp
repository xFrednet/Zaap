#include <Zaap.h>

using namespace zaap;
using namespace math;
using namespace graphics;
using namespace scene;
using namespace std;

Scene* scene_ = nullptr;
LightSetup *lightSetup = nullptr;
Light* light = nullptr;
Light* light2 = nullptr;
Camera* camera = nullptr;
Entity* m1 = nullptr;
Entity* m2 = nullptr;
Entity* lightCube = nullptr;
TerrainTile* terrainTile_;

void loadEntitys()
{
	camera = new ControllableCamera(Vec3(12.0f, 12.0f, -1.0f), -90.0f, 30.0f);
	Renderer::SetCamera(camera);
	{
		lightSetup = new LightSetup();

		light = new Light(Vec3(0.0f, 10.0f, 0.0f), Vec3(1.0f, 0.0f, 1.0f));
		lightSetup->add(light);
		light2 = new Light();
		lightSetup->add(light2);
		lightSetup->setAmbientColor(Color(0.2f, 0.2f, 0.2f));

		scene_->setLightSetup(lightSetup);
	}

	Vec3 v;
	TexturedMesh *mesh = nullptr;
	
	//Test Model
	{
		API::Context::GetLoader()->loadMTLFile("res/oakTree.mtl");
		
		MeshManager::AddMesh(API::Context::GetLoader()->loadOBJFile("oakTree", "res/oakTree.obj", false));
		
		v = Vec3(10, 0, 10);
		scene_->addEntity(new Entity(MeshManager::GetMesh("oakTree"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
	}
	
	{
		API::Context::GetLoader()->loadMTLFile("res/spear.mtl");

		MeshManager::AddMesh(API::Context::GetLoader()->loadOBJFile("spear", "res/spear.obj", false));

		v = Vec3(10, 0, -10);
		scene_->addEntity(new Entity(MeshManager::GetMesh("spear"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
	}
	{
		API::Context::GetLoader()->loadMTLFile("res/bush.mtl");

		MeshManager::AddMesh(API::Context::GetLoader()->loadOBJFile("bush", "res/bush.obj", false));

		v = Vec3(-10, 0, 10);
		scene_->addEntity(new Entity(MeshManager::GetMesh("bush"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
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
		scene_->addEntity(e);
	}

	//rock
	{
		TextureManager::LoadTexture2D("rock", "res/rock.png");
		mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("rock", "res/rock.obj");
		mesh->setTexture((Texture2D*)TextureManager::GetTexture("rock"));
		MeshManager::AddMesh(mesh);
	
		v = Vec3(0, 1, 0);

		scene_->addEntity(new Entity(MeshManager::GetMesh("rock"), v));
	}

	//bench
	{
		TextureManager::LoadTexture2D("wood", "res/bench.jpg");
		mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("bench", "res/bench.obj");
		mesh->setTexture((Texture2D*)TextureManager::GetTexture("wood"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-5, 1, 0);

		scene_->addEntity(new Entity(MeshManager::GetMesh("bench"), v));
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
		scene_->addEntity(m2);
	}

	//Cube 2
	{
		v = Vec3(0, 1, -5);
		m1 = new Entity(tMesh, v);
		scene_->addEntity(m1);
	}

	//Light Cube
	{
		
		v = Vec3(0, -20, 0);
		lightCube = new Entity(tMesh, v);
		scene_->addEntity(lightCube);
	}

	//Zaap frame
	{
		TextureManager::LoadTexture2D("zaap", "res/zaapLogo.png");
		mesh = (TexturedMesh*)API::Context::GetLoader()->loadOBJFile("zaap", "res/zaapFrame.obj");
		mesh->setTexture((Texture2D*)TextureManager::GetTexture("zaap"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-7, 5, 0);
		scene_->addEntity(new Entity(MeshManager::GetMesh("zaap"), v, Vec3(0.0f, 0.0f, 35.0f), Vec3(4.0f, 4.0f, 4.0f)));
	}
	
	//Terrain
	{
		scene::TERRAIN_DESC tDesc;
		tDesc.setupForLowPoly();
		Image bitmap("res\\scene\\heightMap.png");
		terrainTile_ = new TerrainTile(Vec2(-10.0f, -10.0f), &tDesc, bitmap.getSubMap(0, 0, 50, 50));
		terrainTile_->setTexture((Texture2D*)TextureManager::GetTexture("flor"));

	}
}

class Test : public Application
{
public:
	Test() : Application("Test", 852, 480, scene_)
	{}

	float count = 0.0f;
	float count2 = 0.0f;
	float rot = 1.5f;

	void update() override {
		Application::update();

		m1->increaseRotation(Vec3(rot, rot, rot));
		m2->increaseRotation(Vec3(rot, rot, rot));
		count += 0.05f;
		m1->setScale(Vec3(cosf(count) + 1.1f, sinf(count) + 1.1f, sinf(count) + 1.1f));

		count2 += 0.0005f;
		light->setColor(Color(Vec3(1.0f, 1.0f, 1.0f) * (sinf(count2) * 0.25f + 0.75f)));
		
		light->setPosition(Vec3(0.0f, 100.0f, 100.0f * sinf(count2)));

		camera->update();
		lightCube->setPosition(light->getPosition());

		light2->setPosition(camera->getPosition());
	}

	void render() override 
	{
		Application::render();

		terrainTile_->render();
	}
};

int main(void)
{
	scene_ = new Scene();
	
	Test t;
	loadEntitys();

	t.start();

	t.cleanup();

	delete terrainTile_;

	return 0;
}
