#include "visitors.hpp"
#include <iostream>
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void visit_compress(std::unique_ptr<Node>& node){
    for (auto &x: node->children) visit_compress(x);
    if (ends_with(node->type, "Name") || 
    node->type == "type" ||
    node->type == "statement"
    ){
        node = std::move(node->children[0]);
    }

    // Subroutine call has multiple children, so handle differently (peek inside a depth)
    std::vector<std::unique_ptr<Node>> newchildren;
    for (int i = 0; i < (int)node->children.size(); i++){
        if (node->children[i]->type == "subroutineCall"){
            for (int j = 0; j < (int)node->children[i]->children.size(); j++){
                newchildren.push_back(std::move(node->children[i]->children[j]));
            }
        }
        else
        newchildren.push_back(std::move(node->children[i]));
    }

    node->children.clear();
    for (int i = 0; i < (int)newchildren.size(); i++) node->children.push_back(std::move(newchildren[i]));

}