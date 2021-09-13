#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <chrono>

//Made By Ramages

/*
	nodeV is a container for all the nodes, obtained by reading untill the \n character in the file
	connectionsVector is a container for all connections between the nodes, obtained by reading the first two characters after the \n character,
	the correct characters are obtained by looking for the characters before the second \t characters
	matrixVector is a 2D matrix of bools indicating if two nodes have a connection or not
	tempPath is a double ended queue used for storing a temporary version of the path
	finalPath is the full path through the circuit
*/

std::vector<std::string> nodeVector;
std::vector<std::string> connectionsVector;
std::vector<std::vector<bool>> matrixVector;
std::stack<std::string> tempPath;
std::vector<std::string> finalPath;

inline bool file_can_open(const std::string& fileName)
{
	std::ifstream file(fileName);
	return file.good();
}

//Gets the degree of the desired node
inline int getDegree(int i)
{
	int degree = 0;
	for(unsigned long long int j = 0; j < nodeVector.size(); j++)
	{
		if(matrixVector[i][j] == true)
		{
			degree++;
		}
	}
	return degree;
}

//returns true if all the neighbours of a node has been visited
inline bool allVisited(int i)
{
	for(unsigned long long int j = 0; j < nodeVector.size(); j++)
	{
		if(matrixVector[i][j] == true)
		{
			return false;
		}
	}
	return true;
}

//Gets the index in the vector of a given string
inline int getIndex(std::string str)
{
	int index = 0;
	while(str != nodeVector[index])
	{
		index++;
	}
	return index;
}

//Finds the element to become the root of the traversal
inline int findRoot()
{
	int root, degreeCounter = 0;

	for(unsigned long long int i = 0; i < nodeVector.size(); i++)
	{
		if(getDegree(i) % 2 != 0)
		{
			degreeCounter++;
			root = i;
		}
	}

	//1 will represent no path available, otherwise we can start at the assigned root value
	return (degreeCounter != 0 && degreeCounter != 2) ? 1 : root;
}

//Gets all the neccessary input data from the .txt file
inline void dataCollector(char* sourceFile)
{
	std::ifstream file(sourceFile);

	for(std::string content; std::getline(file, content);)
	{
		//The text UNDIRECTED on the frist row will not be included since it's not needed to make the paths
		if(content != "UNDIRECTED")
		{
			//Fills a vector with all nodes. Finds nodes by looking for strings that are empty or without tabs 
			if(content.find('\t') == std::string::npos && content != "")
			{ 
				nodeVector.push_back(content);
			}
			//Fills a vector with all connections. Finds connections by looking for strings containing tabs
			else if(content.find('\t') != std::string::npos && content != "")
			{
				std::vector<char> characters;
				int tabCount = 0;
				
				//Only reads the first two characters since the number (path length) is non essential
				for(char& c : content)
				{
					if(c == '\t' && tabCount <= 1)
					{
						tabCount++;
						if(tabCount < 2)
						{
							characters.push_back(c);
						}
					}
					else if(tabCount <= 1)
					{
						characters.push_back(c);
					}
				}
				std::string subStr(characters.begin(), characters.end());
				connectionsVector.push_back(subStr);
			}
		}
	}
}

//Assigns the values to the 2D vector, true for where a given node has connections, otherwise false
inline void matrixBuilder()
{
	/*
		Strings to help isolate the nodes in the connectionsvector 
		so the match cases only occur when they should, for instance in case of V87	V88 the program doesnt recognize V8 as a substring
		x and y are help variables to set the values of the matrix
	*/
	std::string helperStr;
	std::string front_of_connections;
	std::string back_of_connections;
	int x, y;

	//Build the 2D connections matrix
	for(unsigned long long int i = 0; i < connectionsVector.size(); i++)
	{
		for(unsigned long long int j = 0; j < nodeVector.size(); j++)
		{
			helperStr = connectionsVector[i].c_str();
			front_of_connections = connectionsVector[i].substr(0, connectionsVector[i].find("\t"));
			back_of_connections = connectionsVector[i].substr(connectionsVector[i].find("\t") + 1, helperStr.back());
			if(((nodeVector[j].size() == connectionsVector[i].find("\t")) && (nodeVector[j] == front_of_connections)) || ((nodeVector[j] == back_of_connections) && (nodeVector[j].size() == back_of_connections.size())))
			{
				if(x == -1)
					x = j;
				else
					y = j;
			}
		}
		matrixVector[x][y] = true;
		matrixVector[y][x] = true;
		x = -1;
	}
}

//Finds the Euler circuit or path if one is possible
inline void pathFind(int root)
{
	int ind;

	tempPath.push(nodeVector[root]);

	while(tempPath.size() != 0)
	{
		ind = getIndex(tempPath.top());
		if(allVisited(ind))
		{
			finalPath.push_back(tempPath.top());
			tempPath.pop();
		}
		else
		{
			for(unsigned long long int j = 0; j < nodeVector.size(); j++)
			{
				if(matrixVector[ind][j] == true)
				{
					matrixVector[ind][j] = false;
					matrixVector[j][ind] = false;
					tempPath.push(nodeVector[j]);
					break;
				}
			}
		}
	}
}

int main(int argc, char **argv)
{
	//If the user enters too few arguments
	if(argv[1] == NULL)
	{
		std::cout << "No filepath given, cannot run program" << std::endl;
	}
	else
	{
		//If the user enters too many arguments
		if(argc > 2)
		{
			std::cout << "Cannot run program, too many arguments entered" << std::endl;
		}
		else
		{
			//If the answers file alreay exists, we want to overwrite it
			std::ofstream ofs;
			ofs.open("Answer.txt", std::ofstream::out | std::ofstream::trunc);
			ofs.close();

			//Open the desired file, gets the nodes and connections and put them in their respective vectors
			if(file_can_open(argv[1]))
			{
				dataCollector(argv[1]);
			}
			//If file cant be opened
			else
			{
				throw std::invalid_argument("File not found");
			}

			//We can predetermine the size of the matrix to be the same as the number of nodes times the nubmer of nodes
			matrixVector.resize(nodeVector.size(), std::vector<bool>(nodeVector.size(), false));
			matrixBuilder();

			//If no path can mathematically be found, we don't need to call the pathfinding function
			if(findRoot() == 1)
			{
				std::ofstream write_file;
				write_file.open("Answer.txt", std::ios::out | std::ios::app);
				write_file << "2" << '\n' << "NO PATH FOUND";
				write_file.close();
				std::cout << "NO PATH FOUND" << std::endl;
			}
			//If there is a path to be found
			else
			{
				pathFind(findRoot());
				std::ofstream write_file, time_file;
				write_file.open("Answer.txt", std::ios::out | std::ios::app);
				for(unsigned long long int i = 0; i < finalPath.size() - 1; i++)
				{
					write_file << finalPath[i] << "->";
				}
				write_file << finalPath.back();
				write_file.close();
			}
		}
	}
}