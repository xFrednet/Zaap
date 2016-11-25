using System;
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
			//s.setTerrain(new Terrain("res//scene//", tDesc));
		}
		
	}

	class Program
	{
		static void Main(string[] args)
		{
			CLITest test = new CLITest(new Scene());

			//Bitmap b = new Bitmap("res//scene//HeightMap.png");

			test.start();
			test.cleanup();
			//Console.WriteLine(b.ToString());
		}
	}
}
