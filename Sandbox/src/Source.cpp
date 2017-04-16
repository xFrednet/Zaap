#include <Zaap.h>

using namespace zaap;
using namespace graphics;
using namespace API;
using namespace scene;
using namespace gui;
using namespace std;

Scene* scene_			= nullptr;
LightSetup *lightSetup	= nullptr;
Light* light			= nullptr;
Light* light2			= nullptr;
Camera* camera			= nullptr;
Terrain* terrain_		= nullptr;
GUILabel* label_		= nullptr;
Font font_;

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
	
	//Terrain
	{
		TERRAIN_DESC tDesc;
		tDesc.setup();
		terrain_ = new Terrain("res//scene//", tDesc);
		scene_->setTerrain(terrain_);
	}
	
	//
	// tree
	//
	{
		Texture2D treeTex = TextureCore::CreateTexture2D("res/nature/tree/Texture.png");
		Mesh mesh = Mesh::GetOrLoad("res/nature/tree/Tree.obj");
		mesh.setTexture(treeTex);

		Vec3 pos;
		Vec3 rot(0, 0, 0);
		Entity* tree;
		for (uint i = 0; i < 100; i++)
		{
			pos.X = (float)(rand() % ((uint)terrain_->getHorizontalSize()));
			pos.Z = (float)(rand() % ((uint)terrain_->getVerticalSize()));
			pos.Y = terrain_->getHeight(Vec2(pos.X, pos.Z));

			rot.Y = ZA_PI * 2.0f * (float)((float)(rand() % 100) / 100.0f);

			tree = new Entity(mesh, pos, rot);
			scene_->addEntity(tree);
		}
	}
	//
	// Bush
	//
	{
		Texture2D texture = TextureCore::CreateTexture2D("res/nature/bush/Texture.png");
		Mesh mesh = Mesh::GetOrLoad("res/nature/bush/bush.obj");
		mesh.setTexture(texture);
		Entity* bush = new Entity(mesh, Vec3(10, terrain_->getHeight(Vec2(10, 10)), 10));
		scene_->addEntity(bush);
	}

	long time = clock() - timer;
	ZA_INFO("Scene init took " + std::to_string(time) + "ms");
}

class Test : public Application
{
public:

	float count = 0.0f;
	float count2 = 0.0f;
	float rot = 1.5f;
	uint log = 0;
	bool val = true;
	uint labelCounter = 0;

	Test() : Application("ZAAP testing window", 852, 480, scene_)
	{}

	void update() override {
		Application::update();
		
		count += 0.05f;
		count2 += 0.0005f;
		light->setColor(Color(Vec3(1.0f, 1.0f, 1.0f) * (sinf(count2) * 0.25f + 0.75f)));
		
		light->setPosition(Vec3(0.0f, 1000.0f, 1000.0f * sinf(count2)));

		camera->update();
		
		if (Input::IsKeyDown(ZA_VK_X))
		{
			Vec3 p = camera->getPosition();
			p.Y = terrain_->getHeight(Vec2(p.X, p.Z)) + 1.9f;
			camera->setPosition(p);
		}
		light2->setPosition(camera->getPosition());

		if ((labelCounter++ % 60) == 0)
		{

			String text = "Hello, I'm ZAAP!!\n";
			text += "This is a GUILabel and\n";
			text += "it supports updating text.\n";
			text += "Like this: <";
			
			String updatingText = "******";
			uint loops = (labelCounter / 60) % updatingText.length();
			for (uint i = 0; i < loops; i++)
				text += updatingText.at(i);
			text += ">";
			label_->setText(text);
		}

	}

};

int main(void)
{
	zaap::UUID id1;
	RandomUUID(&id1);
	ZA_INFO(id1);

	//source
	{
		scene_ = new Scene();

		Test t;
		loadEntitys();
		//t.getGUIManager()->add(new gui::GUITextureFrame(Point(0, 0), 225, 100, "res/GUIInfo.png"));
		
		ZA_RESULT zar = 2;
		font_ = FontCore::LoadFont("res/arial.ttf", &zar);
		
		t.getGUIManager()->add(new GUITextureFrame(Point(0, 0), 450, 200, "res/GUIInfo.png"));
		//t.getGUIManager()->add(new GUITextureFrame(Point(0, 0), 450, 200, font_->getCharSheet()));
		label_ = new GUILabel(Point(450, 0), "Changing", font_, 36.0f);
		label_->setBackgroundColor(Color(0.9f, 0.9f, 0.9f, 1.0f));
		label_->setMargin(10, 10, 10, 10);
		label_->setTextColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
		t.getGUIManager()->add(label_);

		t.start();
		
		//delete scene_;

		return 0;
	}
}
