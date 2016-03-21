/**
 * @file   GrpThreadsEtFctor.cxx
 *
 * @author Gaëtan
 *
 * @date   21/03/2016
 *
 * @brief  Concurrence
 *
 * Acces protege par une section critique implementee par un lock_guard
 *
 */
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

using namespace std;
using namespace boost;

enum { KErrArg  = 253 };    // Erreur d'arguments de main()

typedef unsigned long long ULL_t;
typedef          long long  LL_t;

namespace
{
    volatile LL_t  a (0);
    ULL_t NbBoucles;
    mutex Mtx;

    class Incr{
      public :
        void operator() (void){
          for (ULL_t i = 0; i < NbBoucles; ++i)
          {
              lock_guard <mutex> Lock (Mtx);
              ++a;
          }
        }
    };

    class Decr{
      public:
        void operator() (void){
            for (ULL_t i = 0; i < NbBoucles; ++i)
            {
                lock_guard <mutex> Lock (Mtx);
                --a;
            }
        }
    };


} // namespace anonyme

int main (int argc, char * argv [])
{
    if (argc != 3)
    {
       cerr << "Usage : Concurrence <NbThreads> <NbBoucles>\n";
       return KErrArg;
    }
    unsigned NbThreads;
    {
       istringstream is (argv [1]);
       is >> NbThreads;
    }
    {
       istringstream is (argv [2]);
       is >> NbBoucles;
    }
    cout <<   "Nbre de threads : " << NbThreads
         << "\nNbre de boucles : " << NbBoucles << '\n';

    thread_group GrpThreads;

    for (unsigned i = NbThreads; i--; )
    {
       GrpThreads.create_thread(Incr());
       GrpThreads.create_thread(Decr());
    }
    GrpThreads.join_all();

    cout << "a = " << a << '\n';

    return 0;

} // main()
