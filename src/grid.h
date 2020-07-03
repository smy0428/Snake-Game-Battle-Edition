#ifndef GRID_H
#define GRID_H


#include <vector>
#include <string>



class Grid {
	public:
  		Grid(int w, int h);
  		void Clear(int x, int y);
  		void SetHead(int x, int y);
  		void SetBody(int x, int y);
  	    void SetFood(int x, int y);
  		bool CrashBody(int x, int y);
  		std::string GetAt(int x, int y);
  	private:
  		std::vector<std::vector<std::string>> grid;
};

#endif