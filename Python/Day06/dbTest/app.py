from flask import Flask, jsonify, request
from models import db, Product

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///database.db"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False
db.init_app(app)


# 创建数据库和表
@app.before_request
def create_tables():
    db.create_all()
    # 插入示例数据
    products = [
        {
            "name": "Laptop",
            "description": "High performance laptop",
            "price": 1200.50,
            "category": "Electronics",
        },
        {
            "name": "Smartphone",
            "description": "Latest model smartphone",
            "price": 899.99,
            "category": "Electronics",
        },
        {
            "name": "T-shirt",
            "description": "Comfortable cotton T-shirt",
            "price": 19.99,
            "category": "Clothing",
        },
        {
            "name": "Running Shoes",
            "description": "Lightweight running shoes",
            "price": 49.99,
            "category": "Clothing",
        },
        {
            "name": "Blender",
            "description": "High - power blender",
            "price": 79.99,
            "category": "Kitchen",
        },
        {
            "name": "Coffee Maker",
            "description": "Automatic coffee maker",
            "price": 59.99,
            "category": "Kitchen",
        },
    ]
    for product in products:
        new_product = Product(
            name=product["name"],
            description=product["description"],
            price=product["price"],
            category=product["category"],
        )
        db.session.add(new_product)
    db.session.commit()


# 添加商品
@app.route("/add_product", methods=["POST"])
def add_product():
    data = request.json
    new_product = Product(
        name=data["name"],
        description=data.get("description"),
        price=data["price"],
        category=data["category"],
    )
    db.session.add(new_product)
    db.session.commit()
    return jsonify({"message": "Product added successfully"}), 201


# 获取所有商品
@app.route("/products", methods=["GET"])
def get_products():
    products = Product.query.all()
    return jsonify(
        [
            {
                "id": p.id,
                "name": p.name,
                "description": p.description,
                "price": p.price,
                "category": p.category,
            }
            for p in products
        ]
    )


# 根据类别推荐商品
@app.route("/recommend", methods=["GET"])
def recommend_products():
    category = request.args.get("category")
    if not category:
        return jsonify({"error": "Category is required"}), 400
    products = Product.query.filter_by(category=category).all()
    return jsonify(
        [
            {
                "id": p.id,
                "name": p.name,
                "description": p.description,
                "price": p.price,
                "category": p.category,
            }
            for p in products
        ]
    )


if __name__ == "__main__":
    app.run(debug=True)
