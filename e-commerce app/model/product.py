from models import db

class Product(db.Model):
    __tablename__ = 'products'
    
   id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(255), nullable=False)
    description = db.Column(db.Text)
    price = db.Column(db.Numeric(10, 2), nullable=False)
    stock = db.Column(db.Integer, default=0)
    category_id = db.Column(db.Integer, db.ForeignKey('categories.id'))
    created_at = db.Column(db.DateTime, default=db.func.now())
    
   category = db.relationship('Category', backref='products')
    order_items = db.relationship('OrderItem', backref='product', lazy=True)
    
   def to_dict(self):
       return {
         'id': self.id,
         'name': self.name,
         'description': self.description,
         'price': float(self.price),
         'stock': self.stock,
         'category_id': self.category_id,
         'created_at': self.created_at.isoformat()
        }
