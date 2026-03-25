export interface User
{
  id:			number;
  username:		string;
  email:		string;
  avatarUrl:	string | null;
  isActive:		boolean;
  coins?:		number;
  language?:	string;
  a2fActive?:	boolean;
}

export interface RegisterData
{
  username:	string;
  email:	string;
  password:	string;
}

export interface LoginData
{
  email:		string;
  password:		string;
  a2f_code?:	string;
}

export interface AuthResponse
{
  success?:		boolean;
  user?:		User;
  error?:		string;
  requires2FA?:	boolean;
}

export interface TwoFactorResponse
{
  success?:		boolean;
  secret?:		string;
  uri?:			string;
  error?:		string;
}
