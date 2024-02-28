import unittest

class doubly_linked_list_node:
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None

class doubly_linked_list:
    def __init__(self):
        self.head = None
        self.tail = None

    def append(self, data):
        new_node = doubly_linked_list_node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.prev = self.tail
            self.tail.next = new_node
            self.tail = new_node

    def prepend(self, data):
        new_node = doubly_linked_list_node(data)
        if not self.head:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node

    def delete_by_node(self, node: doubly_linked_list_node):
        if node == self.head:
            self.head = node.next
        if node == self.tail:
            self.tail = node.prev
        if node.prev:
            node.prev.next = node.next
        if node.next:
            node.next.prev = node.prev

    def delete_by_data(self, data):
        n = self.find(data)
        if n:
            self.delete_by_node(n)

    def find(self, data):
        current = self.head
        while current:
            if current.data == data:
                return current
            current = current.next
        return None

    def print_list(self):
        current = self.head
        while current:
            print(current.data, end=" ")
            current = current.next
        print()


class doubly_linked_list_test(unittest.TestCase):
    def test_1(self):
        dll = doubly_linked_list()
        dll.append(1)
        dll.append(2)
        dll.append(3)
        dll.prepend(0)
        dll.print_list() 
        
        n = dll.head
        n = n.next
        n = n.next
        dll.delete_by_node(n)
        dll.print_list()     

        dll.delete_by_data(1)   
        dll.print_list()                                                         

if __name__ == '__main__':
    unittest.main()
