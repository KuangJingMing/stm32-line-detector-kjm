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



user_text = """金样学习完成检测完成正在学习检测中请稍后成功线"""
result = remove_duplicates_and_ascii(user_text)
print("结果:", result)
