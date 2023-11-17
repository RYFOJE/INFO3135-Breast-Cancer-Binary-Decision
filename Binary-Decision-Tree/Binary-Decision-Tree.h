#pragma once

#include <functional>

template <typename T>
class Node {

protected:
	Node* leftNode;		/** IF CONDITION EVALUATES TO FALSE **/
	Node* rightNode;	/** IF CONDITION EVALUATES TO TRUE  **/

	const std::function<bool(T)> condition;	/** CONDITION FOR EVALUATION **/

	/**
	 * @brief	Make decision based on condition
	 * @param	T the value used to make the decision
	 * @return	bool the decision made based on the condition (false -> leftNode, true -> rightNode)
	*/
	virtual bool make_decision(const T &val) const {

		if (!condition(val)) {
			return leftNode->make_decision(val);
		}
		else {
			return rightNode->make_decision(val);
		}

	};
	
public:

	/** CONSTRUCTOR **/
	Node(const std::function<bool(T)>& func) : condition(func) {};

	/** GETTERS AND SETTERS **/

	void set_left_node(const Node* node) {
		leftNode = node;
	}

	void set_right_node(const Node* node) {
		rightNode = node;
	}

	Node* get_left_node() const{
		return leftNode;
	}

	Node* get_right_node() const{
		return rightNode;
	}

};

template <typename T>
class RootNode : public Node<T> {

public:
	
	bool process(const T &val) const{
		return Node<T>::make_decision(val);
	}
	
};

template <typename T>
class LeafNode : public Node<T> {

protected:
	
	virtual bool make_decision(T val) const override{

		return Node<T>::condition(val);

	};
};