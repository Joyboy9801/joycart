from models import db

class Order(db.Model):
    __tablename__ = 'orders'
    
   id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey('users.id'), nullable=False)
    total = db.Column(db.Numeric(10, 2), nullable=False)
    status = db.Column(db.String(20), default='pending')
    created_at = db.Column(db.DateTime, default=db.func.now())
    
   items = db.relationship('OrderItem', backref='order', lazy=True, cascade='all, delete-orphan')
    
   def to_dict(self):
       return {
         'id': self.id,
         'user_id': self.user_id,
         'total': float(self.total),
         'status': self.status,
         'created_at': self.created_at.isoformat(),
         'items': [item.to_dict() for item in self.items]
        }

class OrderItem(db.Model):
    __tablename__ = 'order_items'
    
   id = db.Column(db.Integer, primary_key=True)
    order_id = db.Column(db.Integer, db.ForeignKey('orders.id'), nullable=False)
    product_id = db.Column(db.Integer, db.ForeignKey('products.id'), nullable=False)
    quantity = db.Column(db.Integer, nullable=False)
    unit_price = db.Column(db.Numeric(10, 2), nullable=False)
    
   def to_dict(self):
       return {
         'id': self.id,
         'product_id': self.product_id,
         'quantity': self.quantity,
         'unit_price': float(self.unit_price)
         }
