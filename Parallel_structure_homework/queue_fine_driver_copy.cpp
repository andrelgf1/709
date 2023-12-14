/*
 ============================================================================
 Author        : G. Barlas
 Version       : 1.0
 Last modified : September 2019
 License       : Released under the GNU GPL 3.0
 Description   : 
 To compile    : g++ -std=c++17 queue_fine_driver_copy.cpp -o queue_fine_driver_copy -latomic -pthread
 ============================================================================
 */

#include<iostream>
#include<thread>
#include<stdlib.h>
#include "queue_fine_copy.hpp"


//---------------------------------------
int main(int argc, char **argv)
{
  int N=atoi(argv[1]);
  std::unique_ptr<std::thread> t[N];
  queue<int> q;
  int x=1;
  q.push_back(x);
  q.pop_front();
  unsigned int seed=0;
  for(int i=0;i<N;i++)
      t[i] = std::make_unique<std::thread>([&](){

            // int act=rand_r(&seed)%10;
           
              if(i>5)
              {
                  int x = rand_r(&seed)%100;
                  q.push_back(x);
              }
              else
                  q.pop_front();
        //   }
    });
  
  for(int i=0;i<N;i++)
      t[i]->join();
  std::cout << "Size "<< q.size() << std::endl;    
  return 0;
}
    
    
