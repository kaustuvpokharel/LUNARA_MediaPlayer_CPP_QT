# pip install fastapi uvicorn   ->after installing this through terminal
# uvicorn main:app --reload     -> and run the server with this
# This starts the dummy API at http://127.0.0.1:8000.


from fastapi import FastAPI, HTTPException, Header, Depends
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import time

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

fake_user_db = {
    "test@example.com": {
        "password": "mypassword",
        "name": "Test User"
    }
}

# Simulate JWT (in real case, you'd use PyJWT)
def generate_fake_token(email: str):
    return f"fake-jwt-token-for-{email}-{int(time.time())}"

class LoginRequest(BaseModel):
    email: str
    password: str

@app.post("/login")
def login(request: LoginRequest):
    user = fake_user_db.get(request.email)
    if not user or user["password"] != request.password:
        raise HTTPException(status_code=401, detail="Invalid credentials")
    token = generate_fake_token(request.email)
    return {"token": token}


# Dummy token validation
def verify_token(authorization: str = Header(...)):
    if not authorization.startswith("Bearer fake-jwt-token-for-"):
        raise HTTPException(status_code=403, detail="Invalid or missing token")
    return authorization.split(" ")[1]  # token part

@app.get("/profile")
def get_profile(token: str = Depends(verify_token)):
    # Normally you'd decode the token and fetch user info
    return {"user": "Test User", "email": "test@example.com"}
