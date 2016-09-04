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
Entity* m3 = nullptr;
Entity* lightCube = nullptr;
Terrain* terrain_ = nullptr;

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

	Vec3 v;
	TexturedMesh *mesh = nullptr;
	
	//Test Model
	{
		Loader::LoadMTLFile("res/oakTree.mtl");
		
		MeshManager::AddMesh(Loader::LoadOBJFile("oakTree", "res/oakTree.obj", false));
		
		v = Vec3(10, 0, 10);
		scene_->addEntity(new Entity(MeshManager::GetMesh("oakTree"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
	}
	
	{
		Loader::LoadMTLFile("res/spear.mtl");

		MeshManager::AddMesh(Loader::LoadOBJFile("spear", "res/spear.obj", false));

		v = Vec3(10, 0, -10);
		scene_->addEntity(new Entity(MeshManager::GetMesh("spear"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
	}
	{
		Loader::LoadMTLFile("res/bush.mtl");

		MeshManager::AddMesh(Loader::LoadOBJFile("bush", "res/bush.obj", false));

		v = Vec3(-10, 0, 10);
		scene_->addEntity(new Entity(MeshManager::GetMesh("bush"), v, Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f)));
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

		scene_->addEntity(new Entity(MeshManager::GetMesh("rock"), v));
	}

	//bench
	{
		API::Texture::CreateTexture2D("wood", "res/bench.jpg");
		mesh = (TexturedMesh*)Loader::LoadOBJFile("bench", "res/bench.obj");
		mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("wood"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-5, 1, 0);

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
		m2 = new Entity(tMesh, v);
		scene_->addEntity(m2);
	}

	//Cube 2
	{
		v = Vec3(0, 1, -5);
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
		mesh->setTexture((API::Texture2D*)TextureManager::GetTexture("zaap"));
		MeshManager::AddMesh(mesh);

		v = Vec3(-7, 5, 0);
		scene_->addEntity(new Entity(MeshManager::GetMesh("zaap"), v, Vec3(0.0f, 0.0f, 35.0f), Vec3(4.0f, 4.0f, 4.0f)));
	}
	
	//Terrain
	{
		TERRAIN_DESC tDesc;
		tDesc.setupForLowPoly();
		terrain_ = new Terrain("res//scene//", tDesc);

	}

	long time = clock() - timer;
	ZAAP_INFO("Source: Scene init took " + std::to_string(time) + "ms");
}

class Test : public Application
{
public:
	Test() : Application("Test", 852, 480, scene_)
	{}

	float count = 0.0f;
	float count2 = 0.0f;
	float rot = 1.5f;
	uint log = 0;
	bool val;

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

		log++;
		if (log % 10 == 0)
		if (camera->getViewFrustum().isVisible(Vec3(0.0f, 1.0f, 0.0f)))
		{
			if (!val)
			{
				m3->setPosition(Vec3(0.0f, 1.0f, 0.0f));
				ZAAP_INFO("true 1");
				val = true;
			}
		}
		else
		{
			if (val)
			{
				m3->setPosition(Vec3(0.0f, -50.0f, 0.0f));
				ZAAP_INFO("false -50");
				val = false;
			}
		}


		//light2->setPosition(camera->getPosition());
	}

	void render() override 
	{
		Application::render();

		terrain_->render();
	}
};

int main(void)
{
	Plane3D plane(1.0f, 1.0f, 0.0f, -1.0f);
	plane.normalize();

	cout << plane.isPointOnPlane(Vec3(0.0f, -1.0f, 0.0f)) << " " << plane.isPointOnPlane(Vec3(78216.0f, 1212.0f, 22.0f)) << endl;

	Vec3 point = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 p = plane.getClosestPoint(point);
	uint8 r = plane.getRelation(p);
	float d = plane.getSignedDistance(point);
	cout << p.toString() << " " << to_string(r) << " " << d << " " << plane.isPointOnPlane(p) << " " << true << endl;

	point = Vec3(20.0f, 15.0f, 90.0f);
	p = plane.getClosestPoint(point);
	r = plane.getRelation(p);
	d = plane.getSignedDistance(point);
	cout << p.toString() << " " << to_string(r) << " " << d << " " << plane.isPointOnPlane(p) << " " << false << endl;

	point = Vec3(56.0f, -15.0f, 8574894564564564.0f);
	p = plane.getClosestPoint(point);
	r = plane.getRelation(p);
	d = plane.getSignedDistance(point);
	cout << p.toString() << " " << to_string(r) << " " << d << " " << plane.isPointOnPlane(p) << endl;


	scene_ = new Scene();
	
	Test t;
	loadEntitys();

	t.start();

	t.cleanup();

	terrain_->cleanup();
	delete terrain_;

	return 0;
}
