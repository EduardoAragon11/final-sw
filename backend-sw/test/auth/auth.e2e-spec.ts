import { Test, TestingModule } from '@nestjs/testing';
import { INestApplication } from '@nestjs/common';
import request from 'supertest';

import { AppModule } from '../../src/app.module';

describe('Auth E2E', () => {
  let app: INestApplication;

  beforeAll(async () => {
    const moduleFixture: TestingModule = await Test.createTestingModule({
      imports: [AppModule],
    }).compile();

    app = moduleFixture.createNestApplication();
    await app.init();
  });

  afterAll(async () => {
    await app.close();
  });

  it('/auth/login (POST) should return JWT', async () => {
    const res = await request(app.getHttpServer())
      .post('/auth/login')
      .send({
        username: 'admin',
        password: 'adminpass',
      })
      .expect(201);

    expect(res.body.access_token).toBeDefined();
  });

  it('/auth/login (POST) should fail with wrong credentials', async () => {
    await request(app.getHttpServer())
      .post('/auth/login')
      .send({
        username: 'fail',
        password: '123',
      })
      .expect(401);
  });
});
