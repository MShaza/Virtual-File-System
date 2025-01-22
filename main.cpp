#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Node
{
public:
    bool isFile;
    string fileName;
    std::vector<Node*> directoryChildrens;
    Node(string fileName, bool isFile): fileName(fileName), isFile(isFile){}
   
};
class VFS
{
private:
   Node * rootNode;
   Node * currentDirectory;
   VFS(Node* rootNode, Node* curretDirectory): rootNode(new Node("/",false)),currentDirectory(rootNode){}
   Node *checkIfExist(Node* directory, string fileName){
    for(auto directorychild : directory->directoryChildrens){
        if(fileName == directorychild->fileName){
            return directorychild;
        }
    }
    return nullptr;
    
   }
public:
void createDirectory(string fileName, bool isFile);
};
/**
 * @func : Create Directory
 * @parameters : Current Direcorty
*/
void::VFS::createDirectory(string fileName, bool isFile){
    //check if file already exist
      if(checkIfExist(currentDirectory, fileName)){
        cout<<"File already exist"<<endl;
    }
    Node* newNode = new Node(fileName, isFile);
        currentDirectory->directoryChildrens.push_back(newNode);
        std::cout << (isFile ? "File" : "Directory") << " created: " << fileName << "\n";
    }
int main(){

}

