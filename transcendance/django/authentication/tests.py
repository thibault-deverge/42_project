from django.test import TestCase, Client
from django.urls import reverse
from rest_framework import status
from rest_framework.test import APITestCase
from django.contrib.auth import get_user_model

User = get_user_model()

class SignupTest(APITestCase):
    def test_simple_signup(self):
        url = reverse('signup')
        data = {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': 'testpassword123',
            'confirm_password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertTrue(User.objects.filter(username='testuser').exists())
    
    def test_signup_with_taken_username(self):
        url = reverse('signup')
        User.objects.create_user(username='testuser', email='testmail@example.com', password='testpassword1234')
        data = {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': 'testpassword123',
            'confirm_password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
    
    def test_signup_with_taken_email(self):
        url = reverse('signup')
        User.objects.create_user(username='testuser', email='test@example.com', password='testpassword123')
        data = {
            'username': 'testuser2',
            'email': 'test@example.com',
            'password': 'testpassword123',
            'confirm_password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
    
    def test_signup_invalid_format_email(self):
        url = reverse('signup')
        data = {
            'username': 'testuser2',
            'email': 'bademail',
            'password': 'testpassword123',
            'confirm_password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
    
    def test_signup_weak_password_1(self):
        url = reverse('signup')
        data = {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': 'weak',
            'confirm_password': 'weak'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
    
    def test_signup_weak_password_2(self):
        url = reverse('signup')
        data = {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': 'passwordnoNumber',
            'confirm_password': 'passwordnoNumber'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_signup_sql_attack(self):
        url = reverse('signup')
        data = {
            'username': 'SELECT a, b FROM table1 UNION SELECT c, d FROM table2',
            'email': 'test@example.com',
            'password': 'passwordnoNumber',
            'confirm_password': 'passwordnoNumber'
        }
        response = self.client.post(url, data, format='json')
        data = {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': ' ‘ and 1 in (select min(name) from master.dbo.sysdatabases where name >’.’)–',
            'confirm_password': 'passwordnoNumber'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_signup_xss_attack(self):
        url = reverse('signup')
        data = {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': '<script>alert("XSS");</script>',
            'confirm_password': 'passwordnoNumber'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
 
    def test_signup_invalid_username(self):
        url = reverse('signup')
        data = {
            'username': '<sql attack>',
            'email': 'test@example.com',
            'password': 'testpassword123',
            'confirm_password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
    
    def test_signup_missing_username(self):
        url = reverse('signup')
        data= {
            'email': 'test@example.com',
            'password': 'testpassword123',
            'confirm_password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_signup_missing_email(self):
        url = reverse('signup')
        data= {
            'username': 'testuser',
            'password': 'testpassword123',
            'confirm_password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_signup_missing_password(self):
        url = reverse('signup')
        data= {
            'username': 'testuser',
            'email': 'test@example.com'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_signup_missing_confirm_password(self):
        url = reverse('signup')
        data= {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': 'testpassword123'
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

class LoginTest(TestCase):
    url = reverse('login')

    def setUp(self):
        self.credential = {
            'username': 'testuser',
            'email': 'testemail@test.com',
            'password': 'mypassword123'
        }
        User.objects.create_user(**self.credential)
    
    def test_successful_login(self):
        response = self.client.post(self.url, self.credential)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
    
    def test_invalid_username(self):
        self.credential['username'] = '<sqlattack>'
        response = self.client.post(self.url, self.credential)
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
    
    def test_incorrect_password(self):
        self.credential['password'] = 'wrongpassword'
        response = self.client.post(self.url, self.credential)
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_missing_username(self):
        credential_without_username = {
            'password': 'password1234',
        }
        response = self.client.post(self.url, credential_without_username)
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
    
    def test_missing_password(self):
        credential_without_password = {
            'username': 'testuser',
        }
        response = self.client.post(self.url, credential_without_password)
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)


class LogoutTest(APITestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='testuser', email='user@company.com', password='testpassword123')
        self.url = reverse('logout')
    
    def test_logout_successful(self):
        self.client.login(username='testuser', password='testpassword123')
        response = self.client.get(self.url)
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
        self.assertFalse('_auth_user_id' in self.client.session)

    def test_logout_unauthenticated_user(self):
        response = self.client.get(self.url)
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

class AuthenticationTestCase(TestCase):
    def setUp(self):
        # Create a user
        self.user = User.objects.create_user(username='testuser', password='12345678test')
        self.client = Client()
    
    def test_logout_user(self):
        # Login the user 
        self.client.login(username='testuser', password='12345678test')

        # Logout the user
        response = self.client.get(reverse('logout'))
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)

        # Check state of the user
        response = self.client.get(reverse('check_auth'))
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.json(), {'authenticated': False})
    
    def test_authenticated_user(self):
        self.client.login(username='testuser', password='12345678test')
        response = self.client.get(reverse('check_auth'))
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.json(), {'authenticated': True})

    def test_unauthenticated_user(self):
        response = self.client.get(reverse('check_auth'))
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.json(), {'authenticated': False})