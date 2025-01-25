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
void removeDirectory(string directoryName);
};
/**
 * @func : Create Directory
 * @parameters : Current Direcorty, file/directory
 * @returnparameters : None
 * @definition : Create a file and directory
*/
void::VirtualFileSystem::createDirectory(string fileName, bool isFile){
    //check if file already exist
      if(checkIfExist(currentDirectory, fileName)){
        cout<<"File already exist"<<endl;
        return;
    }
    // Create New Node
    Node* newNode = new Node(fileName, isFile);
        currentDirectory->directoryChildrens.push_back(newNode);
        std::cout << (isFile ? "File" : "Directory") << " created: " << fileName << "\n";
        return;
    }
 /**
 * @func : listDirectory
 * @parameters : None
 * @Return : None
 * * @definition : List all the files in the current directory
*/
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
 /**
 * @func : changeDirectory
 * @parameters : Change Directory
 * @Return : None
 * * @definition : change directory from current working space to another
*/
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
 /**
 * @func : RemoveDirecotry
 * @parameters : filename
 * @Return : None
 * @definition : remove the direcotry or file
*/
void::VirtualFileSystem::removeDirectory(string fileName){
    if(fileName == "/"){
        cout<<"Root defualt direcotry cannot be deleted"<<endl;
    }
    Node* toBeDeleted = checkIfExist(currentDirectory, fileName);
   if (toBeDeleted != nullptr) {
        // Find the iterator pointing to the node in the vector
        auto it = std::find(currentDirectory->directoryChildrens.begin(), currentDirectory->directoryChildrens.end(), toBeDeleted);

        if (it != currentDirectory->directoryChildrens.end()) {
            // Free the memory if the node was dynamically allocated
            delete *it;

            // Remove the node from the vector
            currentDirectory->directoryChildrens.erase(it);

            cout << "Directory or file '" << fileName << "' deleted successfully" << endl;
        }
    } else {
        cout << "Directory or file '" << fileName << "' not found" << endl;
    }
}
 /**
 * @func : commandsHelp
 * @parameters : None
 * @Return : None
 * @definition : Information on all he commands we have
 * */
void::VirtualFileSystem::commandsHelp(){
    cout<<"cd <name>        :                  Change Directory"<<endl;
    cout<<"mkdir <name>     :                  Create Diretory"<<endl;
    cout<<"touch <name>     :                  Create file"<<endl;
    cout<<"ls               :                  List all the files in a direcroty"<<endl;
    cout<<"rm <name>        :                  Remove directory/file"<<endl;
}
 /**
 * @func : getCommands
 * @parameters : None
 * @Return : None
 * @definition : get the command breaks down the command
*/
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
         else if(getCommand.substr(0,2) == "rm"){
            fileName = getCommand.substr(3,getCommand.length());
            removeDirectory(fileName);
        }
        else{
            cout<<"Invalid Command! Type help"<<endl;
        }
         cout<<currentDirectory->fileName<<": ";
     }
}
int main(){
    VirtualFileSystem vfs;
    vfs.getCommands();
}
