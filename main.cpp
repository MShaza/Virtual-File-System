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
class VirtualFileSystem
{
private:
   Node * rootNode;
   Node * currentDirectory;
   Node *checkIfExist(Node* directory, string fileName){
    for(auto directorychild : directory->directoryChildrens){
        if(fileName == directorychild->fileName){
            return directorychild;
        }
    }
    return nullptr;
    
   }
public:
VirtualFileSystem(): rootNode(new Node("/",false)),currentDirectory(rootNode){}

void createDirectory(string fileName, bool isFile);
void listDirectory();
void changeDirectory(string directoryName);
void commandsHelp();
void getCommands();
};
/**
 * @func : Create Directory
 * @parameters : Current Direcorty
*/
void::VirtualFileSystem::createDirectory(string fileName, bool isFile){
    //check if file already exist
      if(checkIfExist(currentDirectory, fileName)){
        cout<<"File already exist"<<endl;
        return;
    }
    Node* newNode = new Node(fileName, isFile);
        currentDirectory->directoryChildrens.push_back(newNode);
        std::cout << (isFile ? "File" : "Directory") << " created: " << fileName << "\n";
        return;
    }
void::VirtualFileSystem::listDirectory(){
    if(currentDirectory->directoryChildrens.empty()){
        cout<<"There are no files in the driectory "<<currentDirectory->fileName<<endl;
        return;
    }
    for(auto directoryChildrens:currentDirectory->directoryChildrens){
        cout<<directoryChildrens->fileName<<std::endl;
    }
    return;
}
void::VirtualFileSystem::changeDirectory(string changeDirectory){
    if(changeDirectory == ".."){
        currentDirectory = rootNode;
    }
    else{
        Node* targetDirectory = checkIfExist(currentDirectory, changeDirectory);
        if (targetDirectory != nullptr) {
            // Change current directory to the target directory
            currentDirectory = targetDirectory;
        } else {
            // Directory does not exist
            cout << "Directory does not exist" << endl;
        }
    }
}
void::VirtualFileSystem::commandsHelp(){
    cout<<"cd <name>        :                  Change Directory"<<endl;
    cout<<"mkdir <name>     :                  Create Diretory"<<endl;
    cout<<"touch <name>     :                  Create file"<<endl;
    cout<<"ls               :                  List all the files in a direcroty"<<endl;
    cout<<"rm <name>        :                  Remove directory/file"<<endl;
}
void::VirtualFileSystem::getCommands(){
    string getCommand;
    string fileName;
    cout<<currentDirectory->fileName<<": ";
     while (getline(cin, getCommand)) {

        if (getCommand == "exit") break; // Exit the loop
        else if(getCommand == "ls"){
            listDirectory();
        }
        else if (getCommand.substr(0, 5) =="mkdir")
        {
            fileName = getCommand.substr(6,getCommand.length());
            
            createDirectory(fileName, false);
        }
        else if(getCommand.substr(0, 5) =="touch"){
            fileName = getCommand.substr(6,getCommand.length());
            createDirectory(fileName, true);
        }
        
        else if (getCommand.substr(0,2)=="cd"){
            fileName = getCommand.substr(3,getCommand.length());
            changeDirectory(fileName);
        }
        else if(getCommand == "help"){
            commandsHelp();
        }
         cout<<currentDirectory->fileName<<": ";
     }
}
int main(){
    VirtualFileSystem vfs;
    vfs.getCommands();
}
