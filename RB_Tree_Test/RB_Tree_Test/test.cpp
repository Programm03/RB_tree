#include "pch.h"
#include "../../RB_tree/RB_tree/RB_tree.h"
#include <vector>

TEST(SimpleInsert, TwoElements) {
	RB_Tree tree;

	tree.insert(3);
	tree.insert(2);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 2}, {Color::BLACK, 3} };

  EXPECT_EQ(nodes, expected);

}

TEST(RB_Tree_Repaint, Two_Red_Elements) {
	RB_Tree tree;

	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 1}, {Color::BLACK, 2}, {Color::RED, 3} };

  EXPECT_EQ(nodes, expected);
}

TEST(RB_Tree_Repaint, Rigt_Uncle_Red) {
	RB_Tree tree;

	tree.insert(3);
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 1}, {Color::BLACK, 2}, {Color::BLACK, 3}, {Color::BLACK, 4} };

  EXPECT_EQ(nodes, expected);
}

TEST(RB_Tree_Repaint, Left_Uncle_Red) {
	RB_Tree tree;

	tree.insert(3);
	tree.insert(4);
	tree.insert(2);
	tree.insert(5);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 2}, {Color::BLACK, 3}, {Color::BLACK, 4}, {Color::RED, 5} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Rigth_Left_Unbalance) {
	RB_Tree tree;

	tree.insert(3);
	tree.insert(5);
	tree.insert(4);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 3}, {Color::BLACK, 4}, {Color::RED, 5} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Unbalance_Left_1) {
	RB_Tree tree;

	tree.insert(10);
	tree.insert(9);
	tree.insert(15);
	tree.insert(8);
	tree.insert(7);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 7}, {Color::BLACK, 8}, {Color::RED, 9}, {Color::BLACK, 10}, {Color::BLACK, 15} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Unbalance_Left_2) {
	RB_Tree tree;
	
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 1}, {Color::BLACK, 2}, {Color::RED, 3}, {Color::BLACK, 4}, {Color::BLACK, 5} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Unbalance_Right) {
	RB_Tree tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 1}, {Color::BLACK, 2}, {Color::RED, 3}, {Color::BLACK, 4}, {Color::RED, 5} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Long_Unbalance_Right) {
	RB_Tree tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(8);
	tree.insert(9);
	tree.insert(10);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 1}, {Color::BLACK, 2}, {Color::BLACK, 3}, {Color::BLACK, 4},
										{Color::BLACK, 5}, {Color::BLACK, 6}, {Color::BLACK, 7}, {Color::RED, 8},
										{Color::BLACK, 9}, {Color::RED, 10} };

  EXPECT_EQ(nodes, expected);
};


TEST(Structure_RB_Tree, Random) {
	RB_Tree tree;

	tree.insert(5);
	tree.insert(2);
	tree.insert(10);
	tree.insert(3);
	tree.insert(4);
	tree.insert(14);
	tree.insert(6);
	tree.insert(19);
	tree.insert(21);
	tree.insert(20);
	tree.insert(1);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 1}, {Color::BLACK, 2}, {Color::RED, 3}, {Color::BLACK, 4},
										{Color::BLACK, 5}, {Color::BLACK, 6}, {Color::BLACK, 10}, {Color::BLACK, 14},
										{Color::BLACK, 19}, {Color::RED, 20}, {Color::BLACK, 21} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Big_Numbers) {
	RB_Tree tree;

	std::vector<int> big_nubmers{2341, 4952, 2738, 8267, 7825, 6274, 8726, 9999, 8273, 1342, 2364,
								1423, 7362, 8268, 8263, 7263, 2732, 7546, 5636, 8279};

	for (int i = 0; i < big_nubmers.size(); ++i) {
		tree.insert(big_nubmers[i]);
	}

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 1342}, {Color::RED, 1423}, {Color::RED, 2341}, {Color::BLACK, 2364},
										{Color::RED, 2732}, {Color::BLACK, 2738}, {Color::BLACK, 4952}, {Color::RED, 5636},
										{Color::RED, 6274}, {Color::RED, 7263}, {Color::BLACK, 7362}, {Color::RED, 7546},
										{Color::BLACK, 7825}, {Color::RED, 8263}, {Color::BLACK, 8267}, {Color::RED, 8268},
										{Color::BLACK, 8273}, {Color::RED, 8279}, {Color::BLACK, 8726}, {Color::BLACK, 9999} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Fifteen_Elements_Random) {

	RB_Tree tree;

	std::vector<int> random_numbers{ 15, 20, 23, 8, 6, 11, 29, 4, 39, 34, 9, 5, 48, 19, 7, 26, 12, 30, 14, 46, 28, 1, 
									 16, 25, 50, 47, 45, 43, 41, 3, 37, 44, 2, 13, 40, 10, 22, 31, 35, 24, 17, 32, 21,
									 0, 42, 27, 38, 36, 33, 18, 49 };
	for (int i = 0; i <= 50; ++i) {
		tree.insert(random_numbers[i]);
	}

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 0}, {Color::BLACK, 1}, {Color::RED, 2}, {Color::RED, 3}, {Color::BLACK, 4},
										{Color::BLACK, 5}, {Color::BLACK, 6}, {Color::RED, 7}, {Color::BLACK, 8}, {Color::BLACK, 9},
										{Color::RED, 10}, {Color::RED, 11}, {Color::RED, 12}, {Color::BLACK, 13}, {Color::RED, 14},
										{Color::BLACK, 15}, {Color::BLACK, 16}, {Color::RED, 17}, {Color::RED, 18}, {Color::BLACK, 19},
										{Color::BLACK, 20}, {Color::RED, 21}, {Color::BLACK, 22}, {Color::RED, 23}, {Color::RED, 24},
										{Color::BLACK, 25}, {Color::BLACK, 26}, {Color::RED, 27}, {Color::BLACK, 28}, {Color::RED, 29},
										{Color::BLACK, 30}, {Color::RED, 31}, {Color::BLACK, 32}, {Color::RED, 33}, {Color::BLACK, 34},
										{Color::BLACK, 35}, {Color::RED, 36}, {Color::RED, 37}, {Color::BLACK, 38}, {Color::BLACK, 39},
										{Color::RED, 40}, {Color::BLACK, 41}, {Color::RED, 42}, {Color::BLACK, 43}, {Color::RED, 44},
										{Color::BLACK, 45}, {Color::RED, 46}, {Color::BLACK, 47}, {Color::BLACK, 48}, {Color::RED, 49},
										{Color::BLACK, 50} }; // 50 итреаций проверены вручную! Проверить expected!

	EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Fifteen_Elements_To_Right) {
	RB_Tree tree;

	for (int i = 0; i < 51; ++i) {
		tree.insert(i);
	}

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 0}, {Color::BLACK, 1}, {Color::BLACK, 2}, {Color::BLACK, 3}, {Color::BLACK, 4},
										{Color::BLACK, 5}, {Color::BLACK, 6}, {Color::BLACK, 7}, {Color::BLACK, 8}, {Color::BLACK, 9},
										{Color::BLACK, 10}, {Color::BLACK, 11}, {Color::BLACK, 12}, {Color::BLACK, 13}, {Color::BLACK, 14},
										{Color::BLACK, 15}, {Color::BLACK, 16}, {Color::BLACK, 17}, {Color::BLACK, 18}, {Color::BLACK, 19},
										{Color::BLACK, 20}, {Color::BLACK, 21}, {Color::BLACK, 22}, {Color::BLACK, 23}, {Color::BLACK, 24},
										{Color::BLACK, 25}, {Color::BLACK, 26}, {Color::BLACK, 27}, {Color::BLACK, 28}, {Color::BLACK, 29},
										{Color::BLACK, 30}, {Color::RED, 31}, {Color::BLACK, 32}, {Color::BLACK, 33}, {Color::BLACK, 34},
										{Color::RED, 35}, {Color::BLACK, 36}, {Color::BLACK, 37}, {Color::BLACK, 38}, {Color::BLACK, 39},
										{Color::BLACK, 40}, {Color::BLACK, 41}, {Color::BLACK, 42}, {Color::RED, 43}, {Color::BLACK, 44},
										{Color::BLACK, 45}, {Color::BLACK, 46}, {Color::RED, 47}, {Color::RED, 48}, {Color::BLACK, 49},
										{Color::RED, 50} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Fifteen_Elements_To_Left) {
	RB_Tree tree;

	for (int i = 50; i >= 0; --i) {
		tree.insert(i);
	}

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	// 0, 2, 6, 14, 18 - RED, other black.
	std::vector<InsertedNode> expected{ {Color::RED, 0}, {Color::BLACK, 1}, {Color::RED, 2}, {Color::RED, 3}, {Color::BLACK, 4},
										{Color::BLACK, 5}, {Color::BLACK, 6}, {Color::RED, 7}, {Color::BLACK, 8}, {Color::BLACK, 9},
										{Color::BLACK, 10}, {Color::BLACK, 11}, {Color::BLACK, 12}, {Color::BLACK, 13}, {Color::BLACK, 14},
										{Color::RED, 15}, {Color::BLACK, 16}, {Color::BLACK, 17}, {Color::BLACK, 18}, {Color::RED, 19},
										{Color::BLACK, 20}, {Color::BLACK, 21}, {Color::BLACK, 22}, {Color::BLACK, 23}, {Color::BLACK, 24},
										{Color::BLACK, 25}, {Color::BLACK, 26}, {Color::BLACK, 27}, {Color::BLACK, 28}, {Color::BLACK, 29},
										{Color::BLACK, 30}, {Color::BLACK, 31}, {Color::BLACK, 32}, {Color::BLACK, 33}, {Color::BLACK, 34},
										{Color::BLACK, 35}, {Color::BLACK, 36}, {Color::BLACK, 37}, {Color::BLACK, 38}, {Color::BLACK, 39},
										{Color::BLACK, 40}, {Color::BLACK, 41}, {Color::BLACK, 42}, {Color::BLACK, 43}, {Color::BLACK, 44},
										{Color::BLACK, 45}, {Color::BLACK, 46}, {Color::BLACK, 47}, {Color::BLACK, 48}, {Color::BLACK, 49},
										{Color::BLACK, 50} };

  EXPECT_EQ(nodes, expected);
}

TEST(Structure_RB_Tree, Hundred_Elements) {
	RB_Tree tree;

	std::vector<int> random_elements{ 1, 78, 74, 33, 92, 34, 62, 52, 11, 85, 42, 57, 82, 43, 24, 60, 49, 38, 77,
									  18, 16, 58, 7, 6, 2, 8, 66, 9, 32, 35, 99, 73, 55, 53, 13, 26, 30, 89, 79,
									  10, 27, 90, 31, 44, 70, 87, 93, 71, 5, 68, 37, 50, 96, 88, 20, 25, 29, 61,
									  0, 56, 28, 36, 63, 48, 51, 4, 12, 86, 72, 54, 3, 47, 59, 69, 75, 45, 65, 67,
									  95, 80, 21, 83, 94, 84, 41, 19, 15, 91, 97, 64, 100, 81, 39, 40, 17, 22, 46, 
									  23, 76, 98, 14 };

	for (int i = 0; i < random_elements.size(); ++i) {
		tree.insert(random_elements[i]);
	}

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 0}, {Color::BLACK, 1}, {Color::RED, 2}, {Color::RED, 3}, {Color::BLACK, 4}, {Color::RED, 5},
										{Color::BLACK, 6}, {Color::BLACK, 7}, {Color::RED, 8}, {Color::BLACK, 9}, {Color::RED, 10}, {Color::RED, 11},
										{Color::BLACK, 12}, {Color::BLACK, 13}, {Color::RED, 14}, {Color::BLACK, 15}, {Color::RED, 16}, {Color::BLACK, 17},
										{Color::BLACK, 18}, {Color::BLACK, 19}, {Color::RED, 20}, {Color::RED, 21}, {Color::BLACK, 22}, {Color::RED, 23},
										{Color::BLACK, 24}, {Color::BLACK, 25}, {Color::RED, 26}, {Color::RED, 27}, {Color::BLACK, 28}, {Color::RED, 29},
										{Color::BLACK, 30}, {Color::RED, 31}, {Color::BLACK, 32}, {Color::RED, 33}, {Color::BLACK, 34}, {Color::RED, 35},
										{Color::BLACK, 36}, {Color::BLACK, 37}, {Color::BLACK, 38}, {Color::RED, 39}, {Color::RED, 40}, {Color::BLACK, 41},
										{Color::BLACK, 42}, {Color::BLACK, 43}, {Color::RED, 44}, {Color::BLACK, 45}, {Color::RED, 46}, {Color::BLACK, 47},
										{Color::BLACK, 48}, {Color::RED, 49}, {Color::BLACK, 50}, {Color::RED, 51}, {Color::BLACK, 52}, {Color::BLACK, 53},
										{Color::RED, 54}, {Color::RED, 55}, {Color::BLACK, 56}, {Color::BLACK, 57}, {Color::BLACK, 58}, {Color::RED, 59},
										{Color::BLACK, 60}, {Color::BLACK, 61}, {Color::BLACK, 62}, {Color::RED, 63}, {Color::BLACK, 64}, {Color::RED, 65},
										{Color::RED, 66}, {Color::RED, 67}, {Color::BLACK, 68}, {Color::RED, 69}, {Color::BLACK, 70}, {Color::BLACK, 71},
										{Color::RED, 72}, {Color::BLACK, 73}, {Color::RED, 74}, {Color::RED, 75}, {Color::BLACK, 76}, {Color::RED, 77},
										{Color::RED, 78}, {Color::BLACK, 79}, {Color::BLACK, 80}, {Color::RED, 81}, {Color::BLACK, 82}, {Color::RED, 83},
										{Color::BLACK, 84}, {Color::BLACK, 85}, {Color::RED, 86}, {Color::BLACK, 87}, {Color::RED, 88}, {Color::BLACK, 89},
										{Color::BLACK, 90}, {Color::RED, 91}, {Color::RED, 92}, {Color::RED, 93}, {Color::BLACK, 94}, {Color::RED, 95},
										{Color::BLACK, 96}, {Color::BLACK, 97}, {Color::RED, 98}, {Color::RED, 99}, {Color::BLACK, 100} };

  EXPECT_EQ(nodes, expected);
}

TEST(SimpleErase, Element_Without_Sons) {
	RB_Tree tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);

	tree.erase(1);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 2}, {Color::RED, 3} };

  EXPECT_EQ(nodes, expected);
}

TEST(SimpleErase, Element_With_One_Son) {
	RB_Tree tree;

	tree.insert(9);
	tree.insert(7);
	tree.insert(10);
	tree.insert(11);

	tree.erase(10);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 7}, {Color::BLACK, 9}, {Color::BLACK, 11} };
	
  EXPECT_EQ(nodes, expected);
}

TEST(SimpleErase, No_Element) {
	RB_Tree tree;

	tree.erase(1);

	tree.insert(1);

	tree.erase(2);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::BLACK, 1} };

  EXPECT_EQ(nodes, expected);
}

TEST(SimpleErase, Element_With_Two_Son) {
	RB_Tree tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(0);
	tree.insert(5);
	tree.insert(4);

	tree.erase(4);

	std::vector<InsertedNode> nodes = tree.GetTreeNodes();
	std::vector<InsertedNode> expected{ {Color::RED, 0}, {Color::BLACK, 1}, {Color::BLACK, 2}, {Color::BLACK, 3}, {Color::RED, 5} };

  EXPECT_EQ(nodes, expected);
}