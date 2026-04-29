-- 查询保质期在“2020-02-19”及以后的食品类商品信息
SELECT *
FROM dbo.GoodsInfo
WHERE
    商品类别 = '食品类'
    AND 保质期 >= '2020-02-19';