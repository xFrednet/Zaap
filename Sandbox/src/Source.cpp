#include <Zaap.h>
#include <graphics/Font.h>

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
Entity* m3 = nullptr;
Entity* lightCube = nullptr;
Terrain* terrain_ = nullptr;
Font font_;

void loadEntitys()
{
	clock_t timer = clock();
	camera = new ControllableCamera(Vec3(12.0f, 12.0f, -1.0f), -90.0f, 30.0f);
	((ControllableCamera*)camera)->setSpeed(0.25f);
	Renderer::SetCamera(camera);
	{
		lightSetup = new LightSetup();

		light = new Light(Vec3(0.0f, 10.0f, 0.0f), Vec3(1.0f, 0.0f, 1.0f));
		lightSetup->add(light);
		light2 = new Light(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f));
		lightSetup->add(light2);
		lightSetup->setAmbientColor(Color(0.2f, 0.2f, 0.2f));

		scene_->setLightSetup(lightSetup);
	}
	
	//Terrain
	{
		TERRAIN_DESC tDesc;
		tDesc.setup();
		terrain_ = new Terrain("res//scene//", tDesc);

	}

	Vec3 v;
	TexturedMesh *mesh = nullptr;
	
	//Test Model
	{
		Loader::LoadMTLFile("res/oakTree.mtl");
		
		MeshManager::AddMesh(Loader::LoadOBJFile("oakTree", "res/oakTree.obj", false));
		
		uint x, y;
		for (uint i = 0; i < 50; i++)
		{
			x = rand() % 299;
			y = rand() % 299;
			v = Vec3((float)x, 0, (float)y);
			v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
			scene_->addEntity(new Entity(MeshManager::GetMesh("oakTree"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
		}
	}
	
	{
		Loader::LoadMTLFile("res/spear.mtl");

		MeshManager::AddMesh(Loader::LoadOBJFile("spear", "res/spear.obj", false));

		v = Vec3(10, 0, -10);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
		scene_->addEntity(new Entity(MeshManager::GetMesh("spear"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
	}
	{
		Loader::LoadMTLFile("res/bush.mtl");

		MeshManager::AddMesh(Loader::LoadOBJFile("bush", "res/bush.obj", false));

		uint x, y;
		for (uint i = 0; i < 100; i++)
		{
			x = rand() % 299;
			y = rand() % 299;
			uint loop = rand() % 3;
			for (uint j = 0; j < loop; j++)
			{
				x += rand() % 10 - 5;
				y += rand() % 10 - 5;
				v = Vec3((float)x, 0, (float)y);
				v.Y = terrain_->getHeight(Vec2(v.X, v.Z)) + 0.2f;
				scene_->addEntity(new Entity(MeshManager::GetMesh("bush"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
			}
		}
	}


	//Flor
	{
		API::Texture::CreateTexture2D("flor", "res/flor.jpg");
		mesh = (TexturedMesh*)Loader::LoadOBJFile("flor", "res/flor.obj");
		mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("flor"));
		//((TexturedMesh*)MeshManager::GetMesh("Test"))->setTexture((Texture2D*)TextureManager::GetTexture("flor"));
		MeshManager::AddMesh(mesh);

		v = Vec3(0, -1, 0);
		Entity* e = new Entity(MeshManager::GetMesh("flor"), v);
		e->setScale(5.0f);
		scene_->addEntity(e);
	}

	//rock
	{
		API::Texture::CreateTexture2D("rock", "res/rock.png");
		mesh = (TexturedMesh*)Loader::LoadOBJFile("rock", "res/rock.obj");
		mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("rock"));
		MeshManager::AddMesh(mesh);
	
		v = Vec3(0, 1, 0);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
		scene_->addEntity(new Entity(MeshManager::GetMesh("rock"), v));
	}

	//bench
	{
		API::Texture::CreateTexture2D("wood", "res/bench.jpg");
		mesh = (TexturedMesh*)Loader::LoadOBJFile("bench", "res/bench.obj");
		mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("wood"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-5, 1, 0);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
		scene_->addEntity(new Entity(MeshManager::GetMesh("bench"), v));
	}

	//Cube 1
	API::Texture::CreateTexture2D("cube", "res/cube.png");
	mesh = (TexturedMesh*)Loader::LoadOBJFile("cube", "res/cube.obj");
	mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("cube"));
	MeshManager::AddMesh(mesh);
	Mesh* tMesh = MeshManager::GetMesh("cube");
	{
		v = Vec3(0, 1, 5);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));

		m2 = new Entity(tMesh, v);
		scene_->addEntity(m2);
	}

	//Cube 2
	{
		v = Vec3(0, 1, -5);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));

		m1 = new Entity(tMesh, v);
		scene_->addEntity(m1);
	}
	//test frame
	{
		v = Vec3(0, 1, 0);
		m3 = new Entity(tMesh, v);
		scene_->addEntity(m3);
	}

	//Light Cube
	{
		
		v = Vec3(0, -20, 0);
		lightCube = new Entity(tMesh, v);
		scene_->addEntity(lightCube);
	}

	//Zaap frame
	{
		API::Texture::CreateTexture2D("zaap", "res/zaapLogo.png");
		mesh = (TexturedMesh*)Loader::LoadOBJFile("zaap", "res/zaapFrame.obj");
		mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("font"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-7, 5, 0);
		scene_->addEntity(new Entity(MeshManager::GetMesh("zaap"), v, Vec3(0.0f, 0.0f, 35.0f), Vec3(4.0f, 4.0f, 4.0f)));
	}
	

	long time = clock() - timer;
	ZAAP_INFO("Source: Scene init took " + std::to_string(time) + "ms");
}

class Test : public Application
{
public:

	float count = 0.0f;
	float count2 = 0.0f;
	float rot = 1.5f;
	uint log = 0;
	bool val;

	Test() : Application("Test", 852, 480, scene_)
	{}

	void update() override {
		Application::update();

		m1->increaseRotation(Vec3(rot, rot, rot));
		m2->increaseRotation(Vec3(rot, rot, rot));
		count += 0.05f;
		m1->setScale(Vec3(cosf(count) + 1.1f, sinf(count) + 1.1f, sinf(count) + 1.1f));

		count2 += 0.0005f;
		light->setColor(Color(Vec3(1.0f, 1.0f, 1.0f) * (sinf(count2) * 0.25f + 0.75f)));
		
		light->setPosition(Vec3(0.0f, 1000.0f, 1000.0f * sinf(count2)));

		camera->update();
		lightCube->setPosition(light->getPosition());

		if (camera->getViewFrustum().isVisible(m3->getPosition()))
		{
			if (!val)
			{
				ZAAP_INFO("visible");
				val = true;
			}
		}
		else
		{
			if (val)
			{
				ZAAP_INFO("not visible");
				val = false;
			}
		}

		if (events::Input::IsKeyDown(ZAAP_VK_T))
		{
			Vec3 p = camera->getPosition();
			p.Y = terrain_->getHeight(Vec2(p.X, p.Z));
			m3->setPosition(p);
			log++;
			if (log % 10 == 0)
				ZAAP_INFO(std::to_string(p.Y));
		}
		if (events::Input::IsKeyDown(ZAAP_VK_X))
		{
			Vec3 p = camera->getPosition();
			p.Y = terrain_->getHeight(Vec2(p.X, p.Z)) + 1.9f;
			camera->setPosition(p);
		}

		light2->setPosition(camera->getPosition());
	}

	void render() override 
	{
		Application::render();

		terrain_->render();

		font_.render("A");
	}
};

int main(void)
{
	scene_ = new Scene();
	
	Test t;
	font_ = Font::LoadFTTFile("res/arial.ttf", ZAAP_FONT_128_CHARACTERS);
	loadEntitys();

	t.start();

	t.cleanup();

	return 0;
}
