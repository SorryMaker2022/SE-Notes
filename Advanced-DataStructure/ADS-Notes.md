# 高级数据结构笔记补全计划

## 哈希表：

### 布隆过滤器

TODO

### 布谷鸟哈希

TODO

## 高级搜索树

二叉搜索树是很好用的数据结构，我们（在大部分场合下）能在对数时间内完成对数据的操作。但是在使用二叉搜索树的过程中，如果情况足够不巧（事实上，这种“不巧”的情况不在少数！），二叉搜索树的退化是极为令人头疼的问题。当一棵具有 n 个结点的二叉搜索树退化时，它的数据组织形式趋近于一条链，树高趋近于 `O(n)` 而非 `O(logn)` ，从而产生令人恼火的性能损失。本章注重于引入一些新的机制来实现一棵自平衡的二叉搜索树。这些机制的差异在于它们对二叉搜索树的平衡性要求不太一样————有些机制要求严格的平衡，而另一些机制看起来没那么平衡。这些差异能给这些二叉搜索树带来各异的性能特点，下文将会详细叙述这些机制。

### 跳表

TODO

### AVL树

TODO

### 伸展树

TODO

### 朝鲜树

TODO

### 红黑树

TODO

## 针对数据库的存储结构

众所周知，计算机的各个存储单元之间存在着一个鄙视链：
- CPU Registers
- L1 & L2 Caches
- Last-level Caches (Typically L3 Cache)
- Memory
- Disk (HDD & SSD)

越上层的存储设备，IO速度越快，

### B/B+树

TODO

### LSMT

TODO

## 图上算法

### 最短路问题的dijkstra算法与floyd算法

TODO

### MST问题的kruskal算法与prim算法

TODO

### pagerank算法

TODO

## 其他数据结构与算法

### KD树

TODO

### KMP算法

TODO

## 并行编程

TODO