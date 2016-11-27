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
		public CLITest(Scene s) : base("lol", 800, 600, s)
		{
			TerrainOptions tDesc = new TerrainOptions();
			tDesc.setup();
			s.setTerrain(new Terrain("res//scene//", tDesc));

			Terrain t = s.getTerrain();
			Console.WriteLine("Tüdelü {0}", t.getHeight(new Vector2(10.0f, 2.0f)));
		}
		
	}

	class Program
	{
		static void Main(string[] args)
		{
			string path = Directory.GetCurrentDirectory();
			Console.WriteLine("The current directory is {0}", path);

			CLITest test = new CLITest(new Scene());

			test.start();
			test.cleanup();

			Console.WriteLine("Tüdelü");
		}
	}
}
