#include <Zaap.h>
#include <graphics/Font.h>
#include <util/Loader.h>

using namespace zaap;
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
API::VertexBuffer *fontVB = nullptr;

// TODO https://trello.com/b/vQItmmsf/zaap

void loadEntitys()
{
	clock_t timer = clock();
	camera = new ControllableCamera(Vec3(12.0f, 12.0f, -1.0f), -90.0f, 30.0f);
	((ControllableCamera*)camera)->setSpeed(0.25f);
	scene_->setCamera(camera);
	{
		lightSetup = new LightSetup();

		light = new Light(Vec3(0.0f, 10.0f, 0.0f), Color(1.0f, 0.0f, 1.0f));
		lightSetup->add(light);
		light2 = new Light(Vec3(0.0f, 20.0f, 0.0f), Color(1.0f, 1.0f, 1.0f));
		lightSetup->add(light2);
		lightSetup->setAmbientColor(Color(0.2f, 0.2f, 0.2f));

		scene_->setLightSetup(lightSetup);
	}
	
	//
	//Font
	//
	{
		font_ = Font::LoadFTTFile("res/arial.ttf", ZAAP_FONT_128_CHARACTERS);
		//font_ = Font::LoadFontFromTXT("res/leitice/leitice.txt", "res/leitice/leitice.png", 723);
		fontVB = font_.getVertexBuffer(Loader::LoadFile("text.txt"));
		if (!fontVB)
			ZAAP_INFO("fontVB is NULL");
	}
	//Terrain
	{
		TERRAIN_DESC tDesc;
		tDesc.setup();
		terrain_ = new Terrain("res//scene//", tDesc);
		scene_->setTerrain(terrain_);
	}

	Vec3 v;
	TexturedMesh *textured_mesh;
	

	//Test Model
	{
		MaterialManager::LoadMTLFile("res/oakTree.mtl");
		
		uint x, y;
		for (uint i = 0; i < 50; i++)
		{
			x = rand() % 299;
			y = rand() % 299;
			v = Vec3((float)x, 0, (float)y);
			v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
			scene_->addEntity(new Entity(Mesh::GetOrLoad("res/oakTree.obj", false), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
		}
	}
	
	{
		MaterialManager::LoadMTLFile("res/spear.mtl");

		v = Vec3(10, 0, -10);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
		scene_->addEntity(new Entity(Mesh::GetOrLoad("res/spear.obj", false), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
	}
	{
		MaterialManager::LoadMTLFile("res/bush.mtl");

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
				scene_->addEntity(new Entity(Mesh::GetOrLoad("res/bush.obj", false), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
			}
		}
	}


	//Flor
	{
		API::Texture::CreateTexture2D("flor", "res/flor.jpg");
		textured_mesh = (TexturedMesh*)Mesh::GetOrLoad("res/flor.obj");
		textured_mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("flor"));

		v = Vec3(0, -1, 0);
		Entity* e = new Entity(textured_mesh, v);
		e->setScale(5.0f);
		scene_->addEntity(e);
	}

	//rock
	{
		API::Texture::CreateTexture2D("rock", "res/rock.png");
		textured_mesh = (TexturedMesh*)Mesh::GetOrLoad("res/rock.obj");
		textured_mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("rock"));
	
		v = Vec3(0, 1, 0);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
		scene_->addEntity(new Entity(textured_mesh, v));
	}

	//bench
	{
		API::Texture::CreateTexture2D("wood", "res/bench.jpg");
		textured_mesh = (TexturedMesh*)Mesh::GetOrLoad("res/bench.obj");
		textured_mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("wood"));

		v = Vec3(-5, 1, 0);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));
		scene_->addEntity(new Entity(textured_mesh, v));
	}

	//Cube 1
	API::Texture::CreateTexture2D("cube", "res/cube.png");
	textured_mesh = (TexturedMesh*)Mesh::GetOrLoad("res/cube.obj");
	textured_mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("cube"));
	{
		v = Vec3(0, 1, 5);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));

		m2 = new Entity(textured_mesh, v);
		scene_->addEntity(m2);
	}

	//Cube 2
	{
		v = Vec3(0, 1, -5);
		v.Y = terrain_->getHeight(Vec2(v.X, v.Z));

		m1 = new Entity(Mesh::GetOrLoad("res/cube.obj"), v);
		scene_->addEntity(m1);
	}
	//test frame
	{
		v = Vec3(0, 1, 0);
		m3 = new Entity(Mesh::GetOrLoad("res/cube.obj"), v);
		scene_->addEntity(m3);
	}

	//Light Cube
	{
		
		v = Vec3(0, -20, 0);
		lightCube = new Entity(Mesh::GetOrLoad("res/cube.obj"), v);
		scene_->addEntity(lightCube);
	}

	//Zaap frame
	{
		API::Texture::CreateTexture2D("zaap", "res/zaapLogo.png");
		textured_mesh = (TexturedMesh*)Mesh::GetOrLoad("res/zaapFrame.obj");
		textured_mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("res/leitice/leitice.png"));

		v = Vec3(-7, 5, 0);
		scene_->addEntity(new Entity(textured_mesh, v, Vec3(0.0f, 0.0f, 35.0f), Vec3(4.0f, 4.0f, 4.0f)));
	}


	long time = clock() - timer;
	ZAAP_INFO("Scene init took " + std::to_string(time) + "ms");
}

class Test : public Application
{
public:

	float count = 0.0f;
	float count2 = 0.0f;
	float rot = 1.5f;
	uint log = 0;
	bool val = true;

	Test() : Application("ZAAP testing window", 852, 480, scene_)
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

		if (camera->getViewFrustum().isSphereVisible(m3->getPosition(), 1))
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

		if (Input::IsKeyDown(ZA_VK_T))
		{
			Vec3 p = camera->getPosition();
			p.Y = terrain_->getHeight(Vec2(p.X, p.Z));
			m3->setPosition(p);
			log++;
			if (log % 10 == 0)
				ZAAP_INFO(std::to_string(p.Y));
		}
		if (Input::IsKeyDown(ZA_VK_X))
		{
			Vec3 p = camera->getPosition();
			p.Y = terrain_->getHeight(Vec2(p.X, p.Z)) + 1.9f;
			camera->setPosition(p);
		}
			light2->setPosition(camera->getPosition());


		//light->setColor(Color(1.0f, 0.0f, 0.0f, 0.0f));
		//light2->setColor(Color(1.0f, 0.0f, 0.0f, 0.0f));

	}
	uint timer = 0;
	bool bTemp = true;
	void render() override 
	{
		Application::render();

		font_.render(fontVB, scene_->getRenderer());
		scene_->getRenderer()->presentFrame();
	}
};

int main(void)
{
	zaap::UUID id1;
	RandomUUID(&id1);
	ZAAP_INFO(id1.toString());
	//source
	{
		//Bitmap bm("lolo,guhdawzufgdauiwgfdazuiwetfrgdtauiwegfazuwefdr");
		//cout << bm.contains(0, 0);

		scene_ = new Scene();

		Test t;
	
		loadEntitys();

		t.start();
		
		//delete scene_;

		return 0;
	}
}
