using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ZaapCLI;

namespace Sandbox_CS
{
	class CLITest : Application
	{
		ControllableCamera camera;
		public CLITest(Scene s) : base("Sandbox C#", 800, 600, s)
		{
			TerrainOptions tDesc = new TerrainOptions();
			tDesc.setup();
			s.setTerrain(new Terrain("res//scene//", tDesc));

			camera = new ControllableCamera(new Vector3(0.0f, 0.0f, 0.0f), -90.0f, 30.0f, 90.0f, 1.775f);
			Renderer.SetCamera(camera);

			Light sun = new Light(new Vector3(0.0f, 1000.0f, 0.0f));
			LightSetup lightSetup = new LightSetup();
			lightSetup.add(sun);

			Renderer.LoadLightSetup(lightSetup);
		}
		
		public override void update()
		{
			base.update();

			camera.update();
		}

	}

	class Program
	{
		static void Main(string[] args)
		{
			CLITest test = new CLITest(new Scene());

			test.start();
			test.cleanup();

			GC.Collect();

			Console.WriteLine("Tüdelü");
		}
	}
}
