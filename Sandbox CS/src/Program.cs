using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ZaapCLI;

namespace Sandbox_CS
{
    class Program
    {
        static void Main(string[] args)
        {

            Vector2 v1 = new Vector2(8888.0f, 69.0f);
            Vector2 v2 = new Vector2(112.0f, 5.0f);

            Console.WriteLine("Hello");
            Console.WriteLine("Values v1: {0}, {1}", v1.X, v1.Y);
            Console.WriteLine("Values v2: {0}, {1}", v2.X, v2.Y);
            Console.WriteLine("");
            Console.WriteLine("dot1: {0}", v2.dot(v1));

            v1.normalize();
            v2.normalize();
            v2 = v1;
            Console.WriteLine("Values v1: {0}, {1}", v1.X, v1.Y);
            Console.WriteLine("Values v2: {0}, {1}", v2.X, v2.Y);
            Console.WriteLine("");
            float f = v2.dot(v1);
            Console.WriteLine("dot2: {0}", f);

            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }
    }
}
