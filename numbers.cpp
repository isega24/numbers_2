#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace std;

/**
* This struct save an operation.
*/
struct operation{
   int first;
   char op;
   int second;
   operation(int f,char op, int sec){
      first = f;
      this->op = op;
      second = sec;
   }
};

class Solution{
private:

   /**
   * Distance to the solution. If its a perfect soltion, it will be 0.
   */

   int distance;

   /**
   * operations will save the solution.
   */

   vector<operation> operations;
   

public:
   Solution(){};

   Solution(int distance){
      this->distance=distance;
   }

   /**
   * push_back an operation.
   */
   void push_back(operation op){
      operations.push_back(op);
   }

   /**
   * It returns the vector<operation> of the solution in order.
   */

   vector<operation> pop_operations()const{
      return this->operations;
   }

   /**
   * It return the distance to the solution.
   */

   int dist(){
      return this->distance;
   }
   Solution & operator=(Solution const & other){
      this->distance = other.distance;
      this->operations = other.operations;
      return *this;
   }

   /**
   * This operator say which solution is better. It consider the distance and the
   * numbe of operations.
   */

   bool operator>=(Solution const & sol){
      if(this->distance > sol.distance){
         return true;
      }
      else if(this->distance < sol.distance){
         return false;
      }
      else{
         if(this->operations.size() > sol.operations.size()){
            return true;
         }
         else if(this->operations.size() > sol.operations.size()){
            return false;
         }
         else{
            return true;
         }
      }

   }

   bool operator<=(Solution const & sol){
      if(this->distance < sol.distance){
         return true;
      }
      else if(this->distance > sol.distance){
         return false;
      }
      else{
         if(this->operations.size() < sol.operations.size()){
            return true;
         }
         else if(this->operations.size() > sol.operations.size()){
            return false;
         }
         else{
            return true;
         }
      }
   }

};

ostream & operator<<(ostream & os,Solution const & solution){
   for( int i = solution.pop_operations().size() -1; i>= 0; i--){
      os << solution.pop_operations()[i].first << solution.pop_operations()[i].op;
      os << solution.pop_operations()[i].second;
      if(solution.pop_operations()[i].op != '~'){
         os << '=';
         if( solution.pop_operations()[i].op == '+'){
            os << solution.pop_operations()[i].first + solution.pop_operations()[i].second;
         }
         else if( solution.pop_operations()[i].op == '-'){
            os << solution.pop_operations()[i].first - solution.pop_operations()[i].second;
         }
         else if(solution.pop_operations()[i].op == '*'){
            os << solution.pop_operations()[i].first * solution.pop_operations()[i].second;
         }
         else if(solution.pop_operations()[i].op == '/'){
            os << solution.pop_operations()[i].first / solution.pop_operations()[i].second;
         }
      }
      os << endl;
   }
   return os;
}

Solution solve(vector<int> vect, int number){
   bool found = false;

   Solution solution1(1000); //It is made to be sure that the solution will be instanciated.
   Solution solution2;


   /**
   * We see if the difference of numbers in the vector are just the number founded, so
   * we could finish the algorithm.
   */

   for( int i = 0; i < vect.size(); i++){
      solution2 = Solution(abs(number - vect[i]));
      solution2.push_back(operation(number,'~',vect[i]));
      if(vect[i] == number){
         found = true; 
      }
      if(solution2 <= solution1){
         solution1 = solution2;
      }
   }
   /**
   * If founded, we could not go "down" to look for a better solution, so we return that solution.
   */

   if(found){
      return solution1;
   }
   else{ 

      int aux1,aux2;
      
      vector<int> vect_base,vect_aux;
      for( int i = 0; i < vect.size(); i++){
         for(int j = i+1; j < vect.size(); j++){

            vect_base = vect; // Base vector where we are going to pop i and j-numbers

            aux1 = vect_base[i]; // bouth of them saved here.
            aux2 = vect_base[j];
            vect_base.erase(vect_base.begin()+j);  // deleted.
            vect_base.erase(vect_base.begin()+i);

            vect_aux = vect_base;            // vect_aux will be the one that is going to call the function.
            vect_aux.push_back(aux1+aux2);   // with the i,j-numbers operated(+,-,*,/)
            solution2 = solve(vect_aux,number);
            solution2.push_back(operation(aux1,'+',aux2));
            if(solution2 <= solution1){
               solution1 = solution2;
            }

            vect_aux = vect_base;
            vect_aux.push_back(aux1*aux2);
            solution2 = solve(vect_aux,number);
            solution2.push_back(operation(aux1,'*',aux2));
            if(solution2 <= solution1){
               solution1 = solution2;
            }
            if(aux1 != aux2){
               vect_aux = vect_base;
               if(aux1 > aux2){
                  vect_aux.push_back(aux1-aux2);
                  solution2 = solve(vect_aux,number);
                  solution2.push_back(operation(aux1,'-',aux2));

               }
               else{
                  vect_aux.push_back(aux2-aux1);
                  solution2 = solve(vect_aux,number);
                  solution2.push_back(operation(aux2,'-',aux1));
               }
               if(solution2 <= solution1){
                  solution1 = solution2;
               }
            }
            if(aux2 != 0){
               if(aux1 % aux2 == 0){
                  vect_aux = vect_base;
                  vect_aux.push_back(aux1/aux2);
                  solution2 = solve(vect_aux,number);
                  solution2.push_back(operation(aux1,'/',aux2));
                  if(solution2 <= solution1){
                     solution1 = solution2;
                  }
               }
            }
            if(aux1 != 0){
               if(aux2 % aux1 == 0){
                  vect_aux = vect_base;
                  vect_aux.push_back(aux2/aux1);
                  solution2 = solve(vect_aux,number);
                  solution2.push_back(operation(aux2,'/',aux1));
                  if(solution2 <= solution1){
                     solution1 = solution2;
                  }
               }
            }
         }
      }

      return solution1;
   }

}

int main(int argc, char const *argv[])
{
   vector<int> vect;


   for( int i = 1; i < argc - 1; i++){
      vect.push_back(atoi(argv[i]));
   }

   Solution solution = solve(vect,atoi(argv[argc-1]));

   if(solution.dist() != 0){
      cout << "Imposible to solve, but the best solution is:\n";
   }
   cout << solution;
   return 0;
}