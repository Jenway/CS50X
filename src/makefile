# 主目录makefile
CC = gcc
CFLAGS = -Wall -Werror -std=c11
LDLIBS = -lcs50
SUBDIRS = src # 指定子目录
LIBS = libcs50 # 指定第三方库
all: $(LIBS) $(SUBDIRS) # 目标是第三方库和子目录

$(LIBS): # 对第三方库执行
    $(MAKE) -C $@ # 进入第三方库目录并调用其makefile

$(SUBDIRS): # 对每个子目录执行
    $(MAKE) -C $@ # 进入子目录并调用其makefile

.PHONY: all $(LIBS) $(SUBDIRS) clean # 声明伪目标

clean: # 清理规则
    for dir in $(LIBS) $(SUBDIRS); do \
        $(MAKE) -C $$dir clean; \
    done # 遍历每个第三方库和子目录并执行其清理规则