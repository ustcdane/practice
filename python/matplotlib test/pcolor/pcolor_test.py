#coding:gbk
import numpy as np

# not show the
#import matplotlib
#matplotlib.use('Agg')

from matplotlib.font_manager import FontProperties
from matplotlib import rcParams
import pdb as pdb
import matplotlib.pyplot as plt
import six
from pylab import *



def plot_attention(src_words, trg_words, attention_matrix, file_name=None):
    """This takes in source and target words and an attention matrix (in numpy format)
    and prints a visualization of this to a file.
    :param src_words: a list of words in the source
    :param trg_words: a list of target words
    :param attention_matrix: a two-dimensional numpy array of values between zero and one,
      where rows correspond to source words, and columns correspond to target words
    :param file_name: the name of the file to which we write the attention
    """
    print src_words, trg_words
    print attention_matrix
    fig, ax = plt.subplots()
    # a lazy, rough, approximate way of making the image large enough
    fig.set_figwidth(int(len(trg_words) * 1.6))

    # put the major ticks at the middle of each cell
    ax.set_xticks(np.arange(attention_matrix.shape[1]) + 0.5, minor=False)
    ax.set_yticks(np.arange(attention_matrix.shape[0]) + 0.5, minor=False)
    ax.invert_yaxis()

    # label axes by words
    ax.set_xticklabels(trg_words, minor=False)
    ax.set_yticklabels(src_words, minor=False)
    ax.xaxis.tick_top()
    plt.setp(ax.get_xticklabels(), rotation=50, horizontalalignment='right')
    # draw the heatmap
    plt.pcolor(attention_matrix, cmap=plt.cm.Blues, vmin=0, vmax=1)
    plt.colorbar()

    if file_name != None:
        plt.savefig(file_name, dpi=100)
        #plt.show()
    else:
        print 'show'
        plt.show()
    plt.close()


src = ['a', 'b', 'c']
targ = ['a1', 'b1', 'c1']
# mr=np.array([[0.2,0.8], [0.5,0.5]])
mr = np.random.rand(3, 3)
plot_attention(src, targ, mr,'my_pcolor.png')

