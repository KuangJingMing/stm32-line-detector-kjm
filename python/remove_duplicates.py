def remove_duplicates(text):
    seen = set()
    result = []
    
    for char in text:
        if char not in seen:
            seen.add(char)
            result.append(char)
    
    return ''.join(result)

def remove_ascii_chars(text):
    """删除所有ASCII字符，只保留非ASCII字符（如中文等）"""
    result = []
    for char in text:
        if ord(char) > 127:  # ASCII字符的编码值都在0-127范围内
            result.append(char)
    return ''.join(result)

def remove_duplicates_and_ascii(text):
    """先删除重复字符，再删除ASCII字符"""
    # 先去重
    no_duplicates = remove_duplicates(text)
    # 再删除ASCII字符
    return remove_ascii_chars(no_duplicates)



user_text = """结果: 结果全局变量定义引脚映射表数线束检测器初始化输出锁存入配金样学习成功置参清空响应模式关系（自动）逐一激励每个端进行设所有为高电平默认状态只将当前低到延时稳读取分析，寻找对的示连通判断逻辑正常：恢复完以上率验证编号效性制改比较函首先不匹假已排序便于简单冒泡收集记录统计包括短路情况防止组越界位掩码仅支持调试列用标经处理过查是否在多可能具相同其他使主打印信息或无后续中修第步二三故障类型、错非期望接生报告缓冲区大小实际写字符头部总开详细涉及影算合格快速指获等待户准备品执循环下次此添加交互结果: 学习引脚映射关系（自动金样）报告缓冲区指针大小清空添加开始信息到总数表逐一激励每个端进行设置所有输出为高电平默认状态只将当前低延时稳定读取入分析响应，寻找对的示连通判断逻辑正常：成功无路故障多重短恢复结果率完以上✓失败✗过"""
result = remove_duplicates_and_ascii(user_text)
print("结果:", result)
