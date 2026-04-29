-- 查询食品类的商品数
SELECT COUNT(*) AS 食品类商品数 FROM dbo.GoodsInfo WHERE 商品类别 = '食品';