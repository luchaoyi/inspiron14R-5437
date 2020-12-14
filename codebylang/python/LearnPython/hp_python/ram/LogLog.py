#coding:utf8
#mmh3 Python wrapper for MurmurHash (MurmurHash3), a set of fast and robust hash functions
#mmh3支持对字符串散列，不支持散列数字
#python自带的hash会将数字散列为自身 hash(1) == 1 
#当n不是特别大时，其估计误差过大

def trailing_zeroes(num):
    """Counts the number of trailing 0 bits in num."""
    if num == 0:
        return 32 # Assumes 32 bit integer inputs!
    p = 0
    while (num >> p) & 1 == 0: #为了方便，这个实现中统计的是0尾缀而不是0前缀；其效果是等价的
        p += 1
    return p
 
def estimate_cardinality(values, k):

    num_buckets = 2 ** k
    max_zeroes = [0] * num_buckets
    for value in values:
        h = hash(value)
        bucket = h & (num_buckets - 1) # Mask out the k least significant bits as bucket ID
        bucket_hash = h >> k
        max_zeroes[bucket] = max(max_zeroes[bucket], trailing_zeroes(bucket_hash))
    return 2 ** (float(sum(max_zeroes)) / num_buckets) * num_buckets * 0.79402 #这种预测方法存在一个可预测的偏差；魔法数字0.79402是对这个偏差的修正
    
