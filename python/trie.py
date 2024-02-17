from typing import List

'''
trie with insert, find, delete operations
'''

class TrieNode:
    def __init__(self):
        self.children: List['TrieNode']  = [None]*256
        self.value: str = ''

class Trie:
    def __init__(self):
        self.root = TrieNode()   

    def insert(self, key: str):
        node: TrieNode = self.root
        for i in range(len(key)):
            ascii_index = ord(key[i])
            if node.children[ascii_index] == None:
                node.children[ascii_index] = TrieNode()
            node = node.children[ascii_index]
        node.value = key

    def find(self, key: str) -> str:
        node: TrieNode = self.root
        for i in range(len(key)):
            ascii_index = ord(key[i])
            if node.children[ascii_index] == None:
                return None
            node = node.children[ascii_index]
        return node.value
    
    def delete(self, key: str):
        self._delete(self.root, key)

    def _delete(self, node: TrieNode, key: str) -> TrieNode:
        if key != '':
            ascii_index = ord(key[0])
            node.children[ascii_index] = self._delete(node.children[ascii_index], key[1:])
            return node
        else:
            if node.value != '':
                node.value = ''
            for child in node.children:
                if child != None:
                    return node
            return None

def main():
    t: Trie = Trie()
    t.insert('the')
    t.insert('theaaa')

    print(t.find('the'))
    print(t.find('theaaa'))
    t.delete('the')
    print(t.find('theaaa'))

if __name__ == '__main__':
    main()