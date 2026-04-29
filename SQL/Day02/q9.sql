-- 查询食品类或文具类、库存量不少于50的商品信息
SELECT *
FROM dbo.GoodsInfo
WHERE
    商品类别 IN ('食品类', '文具类')
    AND 库存量 >= 50;