#ifndef _VISITORS_HPP_
#define _VISITORS_HPP_

#include "../parsing/expr_node.hpp"

/**
 * Removes various wrapper classes, like <*Name>, <type> 
 */

void visit_compress(std::unique_ptr<Node>& node);

#endif