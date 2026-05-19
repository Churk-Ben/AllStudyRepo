SELECT CustomerInfo.客户编号, CustomerInfo.客户姓名, OrderList.*
FROM CustomerInfo
JOIN OrderList ON CustomerInfo.客户编号 = OrderList.客户编号
JOIN GoodsInfo ON OrderList.商品编号 = GoodsInfo.商品编号
WHERE GoodsInfo.生产商 = '新新文化用品制造厂'
