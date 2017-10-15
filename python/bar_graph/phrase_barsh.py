# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
from pylab import *
import numpy as np
mpl.rcParams['font.sans-serif'] = ['SimHei'] #指定默认字体
mpl.rcParams['axes.unicode_minus'] = False #解决保存图像是负号'-'显示为方块的问题

def drawBarChartPoseRatio():
    n_groups = 4
    score_26 = (26.93, 27.02, 27.16, 26.40)
    score_9 = (17.17, 17.35, 16.94, 16.78)

    fig, ax = plt.subplots()
    index = np.arange(n_groups)
    bar_width = 0.3
    opacity = 0.4

    rects1 = plt.bar(index,  score_26, bar_width / 2, alpha=opacity, color='r', label='26key')
    rects2 = plt.bar(index + bar_width / 2, score_9, bar_width / 2, alpha=opacity, color='g', label='9key')


    plt.xlabel(u'LSTM模型')
    plt.ylabel(u'错误率降低(%)')
    plt.title(u'较线上组词错误率降低(TOP3)')


    plt.xticks(index - 0.2 + 2 * bar_width, ('33101_embed64_hidden_448', '33276_embed60_hidden448', '33276_embed70_hidden256', '40710_embed50_hidden448'), fontsize=10)
    plt.yticks(fontsize=13)  # change the num axis size

    plt.ylim(15, 28.66)  # The ceil
    plt.legend()
    plt.tight_layout()
    plt.show()


drawBarChartPoseRatio()

