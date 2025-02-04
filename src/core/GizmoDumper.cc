#include "core/GizmoDumper.h"
#include "core/State.h"
#include "core/ModuleInstantiation.h"
#include <algorithm>
#include <iterator>
#include <ostream>
#include <string>
#include <sstream>
#include <boost/regex.hpp>

#include "utils/printutils.h"

#include "core/node.h"
#include "core/ColorNode.h"
#include "core/TransformNode.h"
#include "core/ImportNode.h"


/*!
   \class GizmoDumper

   A visitor responsible for creating a text dump of a node tree.  Also
   contains a cache for fast retrieval of the text representation of
   any node or subtree.
 */

/*!
   Called for each node in the tree.
 */
Response GizmoDumper::visit(State& state, const AbstractNode& node)
{
  if (state.isPrefix()) {
    // LOG(node.name());
    // LOG("Prefix");
    if (
      dynamic_cast<const GroupNode*>(&node)
      || dynamic_cast<const ColorNode*>(&node)
    ) {
      return Response::ContinueTraversal;
    }

    if (const TransformNode* tnode = dynamic_cast<const TransformNode*>(&node)) {
      stringStack.push_back(tnode->toString());
      return Response::ContinueTraversal;
    }

    if (const ImportNode* rnode = dynamic_cast<const ImportNode*>(&node)) {
      // if (rnode->filename.substr(0, 7) == "/gizmo/") {
      // LOG("Import found");
      // LOG(rnode->filename.c_str());
      if (rnode->filename.find("gizmo/") != std::string::npos) {
        // LOG("Gizmo found");
        // LOG(rnode->filename.c_str());
        for (auto& s : stringStack) {
          // LOG(s.c_str());
          this->dumpstream << s << ";";
        }
        this->dumpstream << rnode->toString() << ";" << std::endl;
      }

      return Response::PruneTraversal;
    }

    return Response::PruneTraversal;
  } else if (state.isPostfix()) {
    if (const TransformNode* tnode = dynamic_cast<const TransformNode*>(&node)) {
      stringStack.pop_back();
      return Response::ContinueTraversal;
    }

    // LOG(node.name().c_str());
    // LOG("Postfix");
    return Response::ContinueTraversal;
  }

  return Response::ContinueTraversal;
}

