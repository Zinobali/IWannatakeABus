#ifndef GLOBAL_H
#define GLOBAL_H

constexpr int LINE_INFO_WIDTH = 0;   // 预留边框用于信息展示
constexpr int MARGIN = 30;           // 视图左边距
constexpr int NET_WIDTH = 2000;      // 网络图最大宽度
constexpr int NET_HEIGHT = 2000;     // 网络图最大高度
constexpr int SCENE_WIDTH = (LINE_INFO_WIDTH + MARGIN * 2 + NET_WIDTH);    // 视图宽度
constexpr int SCENE_HEIGHT = (MARGIN * 2 + NET_HEIGHT);                    // 视图高度

constexpr int EDGE_PEN_WIDTH = 2;    // 线路边宽
constexpr int NODE_HALF_WIDTH = 3;   // 节点大小

#endif // GLOBAL_H
