#ifndef __NODE_H__
# define __NODE_H__

# define M_BLACK	0
# define M_RED		1

namespace	ft {
	template<class T>
	class	node {
		public:
			typedef T			value_type;
			typedef T&			reference;
			typedef T*			pointer;
			typedef const T*	const_pointer;
			typedef const T&	const_reference;

			node		*parent;
			node		*left;
			node		*right;
			value_type	content;
			bool		color;

			node() : color(M_RED) {}
			node(const value_type value, node *nill) : parent(nill), left(nill), right(nill), content(value), color(M_RED) {}
			node(const node &other) : parent(other.parent), left(other.left), right(other.right), content(other.content), color(other.color) {}
			~node() {}

			node	*getGrandParent() {
				return (parent->parent);
			}

			node	*getSuccesor(node *nill) {
				node	*s = right;
				while (s != nill && s->left != nill)
					s = s->left;
				return (s);
			}

			node	*&getSibling() {
				if (this == parent->right)
					return (parent->left);
				return (parent->right);
			}
	};

	template<class Node>
	struct	node_traits {
		typedef typename Node::value_type		value_type;
		typedef typename Node::reference		reference;
		typedef typename Node::pointer			pointer;
	};
	template<class NodePtr>
	struct	node_traits<NodePtr*> {
		typedef NodePtr							node;
		typedef typename node::value_type		value_type;
		typedef typename node::reference		reference;
		typedef typename node::pointer			pointer;
	};
	template<class NodePtr>
	struct	node_traits<const NodePtr*> {
		typedef NodePtr							node;
		typedef typename node::value_type		value_type;
		typedef typename node::const_reference	reference;
		typedef typename node::const_pointer	pointer;
	};
}

#endif
