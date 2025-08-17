ecommerce-api/
├── app.py                 # Main Flask application
├── config.py              # Configuration settings
├── requirements.txt       # Python dependencies
├── run.py                 # Application entry point
│
├── models/                # Database models
│   ├── __init__.py
│   ├── user.py
│   ├── product.py
│   ├── category.py
│   ├── cart.py
│   └── order.py
│
├── routes/                # API routes
│   ├── __init__.py
│   ├── auth.py
│   ├── products.py
│   ├── cart.py
│   ├── orders.py
│   └── admin.py
│
├── services/              # Business logic
│   ├── __init__.py
│   ├── auth_service.py
│   ├── product_service.py
│   ├── cart_service.py
│   └── order_service.py
│
├── utils/                 # Utility functions
│   ├── __init__.py
│   ├── decorators.py
│   ├── validators.py
│   └── helpers.py
│
├── static/                # Static files
│   ├── css/
│   ├── js/
│   └── images/
│
├── templates/             # HTML templates
│   ├── base.html
│   ├── index.html
│   ├── products.html
│   ├── cart.html
│   └── admin.html
│
├── tests/                 # Test files
│   ├── __init__.py
│   ├── test_auth.py
│   ├── test_products.py
│   ├── test_cart.py
│   └── test_orders.py
│
├── migrations/            # Database migrations
│   └── versions/
│
└── docs/                  # Documentation
    ├── api.md
    └── database.md
